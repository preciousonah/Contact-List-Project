#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Info::Info() {
    this->name = "No Name Set";
    this->value = "No Value Set";
    this->next = nullptr;
}

Info::Info(std::string name, std::string value, Info *next) {
    this->name = name;
    this->value = value;
    this->next = next;
}

Contact::Contact() {
    this->first = "No First Set";
    this->last = "No Last Set";
    this->next = nullptr;
    this->headInfoList = nullptr;
}

Contact::Contact(std::string first, std::string last, Contact *next) {
    this->first = first;
    this->last = last;
    this->next = next;
    this->headInfoList = nullptr;
}

ContactList::ContactList() {
    this->headContactList = nullptr;
    this->count = 0;
}

int ContactList::getCount() {
    return this->count;
}

bool ContactList::printContact(std::ostream &os, std::string first, std::string last) {
    Contact *current = headContactList;
    while (current != nullptr) {
        if (current->first == first && current->last == last) {
            os << "Contact Name: " << first << " " << last << std::endl;
            Info *infoCurrent = current->headInfoList;
            while (infoCurrent != nullptr) {
                os << infoCurrent->name << " | " << infoCurrent->value << std::endl;
                infoCurrent = infoCurrent->next;
            }
            return true; 
        }
        current = current->next;
    }
    return false; 
}


void ContactList::print(std::ostream &os) {
    Contact *current = headContactList;
    // if (!current) {
    //     os << "Contact list is empty." << std::endl;
    //     return;
    // }
    while (current != nullptr) {
        os << "Contact Name: " << current->first << " " << current->last << std::endl;
        Info *infoCurrent = current->headInfoList;
        while (infoCurrent != nullptr) {
            os << infoCurrent->name << " | " << infoCurrent->value << std::endl;
            infoCurrent = infoCurrent->next;
        }
        current = current->next;
    }
}

bool ContactList::addContact(std::string first, std::string last) {
    Contact* newContact = new Contact(first, last);
    Contact* temp = headContactList;
    while (temp != nullptr) {
        if (temp->first == first && temp->last == last) {
            delete newContact; 
            return false; 
        }
        temp = temp->next;
    }

    if (headContactList == nullptr) {
        headContactList = newContact; 
    } else {
        temp = headContactList;
        while (temp->next != nullptr) {
            temp = temp->next; 
        }
        temp->next = newContact; 
    }
    count++;
    return true;
}

bool ContactList::addInfo(std::string first, std::string last, std::string infoName, std::string infoVal) {
    Contact* current = headContactList;
    while (current != nullptr) {
        if (current->first == first && current->last == last) {
            Info* infoCurrent = current->headInfoList;
            Info* infoPrevious = nullptr;
            while (infoCurrent != nullptr) {
                if (infoCurrent->name == infoName) {
                    infoCurrent->value = infoVal;
                    return true;
                }
                infoPrevious = infoCurrent;
                infoCurrent = infoCurrent->next;
            }

            Info* newInfo = new Info(infoName, infoVal);
            if (infoPrevious == nullptr) {
                current->headInfoList = newInfo;
            } else {
                infoPrevious->next = newInfo;
            }
            return true;
        }
        current = current->next;
    }

    return false;
}

bool ContactList::addContactOrdered(std::string first, std::string last) {
    Contact* newContact = new Contact(first, last);

    Contact* current = headContactList;
    Contact* previous = nullptr;
    while (current != nullptr) {
        if (current->first == first && current->last == last) {
            delete newContact;
            return false;
        }

        if (current->last > last || (current->last == last && current->first > first)) {
            break;
        }

        previous = current;
        current = current->next;
    }

    if (previous == nullptr) {
        newContact->next = headContactList;
        headContactList = newContact;
    } else {
        newContact->next = previous->next;
        previous->next = newContact;
    }

    count++;
    return true;
}


bool ContactList::addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal) {
    Contact* currentContact = headContactList;
    while (currentContact != nullptr) {

        if (currentContact->first == first && currentContact->last == last) {
    
            Info* currentInfo = currentContact->headInfoList;
            Info* prevInfo = nullptr;
            while (currentInfo != nullptr && currentInfo->name < infoName) {
                prevInfo = currentInfo;
                currentInfo = currentInfo->next;
            }

            if (currentInfo != nullptr && currentInfo->name == infoName) {
                currentInfo->value = infoVal;
                return true;
            }

            Info* newInfo = new Info(infoName, infoVal);
            if (prevInfo == nullptr) { 
                newInfo->next = currentContact->headInfoList;
                currentContact->headInfoList = newInfo;
            } else {
                newInfo->next = prevInfo->next;
                prevInfo->next = newInfo;
            }

            return true; 
        }
        currentContact = currentContact->next;
    }


    return false;
}

bool ContactList::removeContact(std::string first, std::string last) {
    Contact* current = headContactList;
    Contact* previous = nullptr;

    while (current != nullptr) {
        if (current->first == first && current->last == last) {
            Info* infoCurrent = current->headInfoList;
            while (infoCurrent != nullptr) {
                Info* tempInfo = infoCurrent;
                infoCurrent = infoCurrent->next;
                delete tempInfo; 
            }

            if (previous == nullptr) {
                headContactList = current->next;
            } else {
                previous->next = current->next;
            }
            delete current; 
            count--; 
            return true;
        }
        previous = current;
        current = current->next;
    }

    return false;
}

bool ContactList::removeInfo(std::string first, std::string last, std::string infoName) {
    Contact* contact = headContactList;
    while (contact != nullptr) {
        if (contact->first == first && contact->last == last) {
            Info* currentInfo = contact->headInfoList;
            Info* previousInfo = nullptr;
            while (currentInfo != nullptr) {
                if (currentInfo->name == infoName) {
                    if (previousInfo == nullptr) {
                        contact->headInfoList = currentInfo->next;
                    } else {
                        previousInfo->next = currentInfo->next;
                    }
                    delete currentInfo;
                    return true;
                }
                previousInfo = currentInfo;
                currentInfo = currentInfo->next;
            }
            return false;
        }
        contact = contact->next;
    }

    return false;
}


ContactList::~ContactList() {
    Contact* currentContact = headContactList;
    while (currentContact != nullptr) {
        Info* currentInfo = currentContact->headInfoList;
        while (currentInfo != nullptr) {
            Info* tempInfo = currentInfo;
            currentInfo = currentInfo->next; 
            delete tempInfo; 
        }

        Contact* tempContact = currentContact;
        currentContact = currentContact->next;
        delete tempContact; 
    }

    headContactList = nullptr;
}


ContactList::ContactList(const ContactList &src) : headContactList(nullptr), count(0) {
    Contact *srcCurrent = src.headContactList, *lastNewContact = nullptr;

    while (srcCurrent != nullptr) {
        Contact *newContact = new Contact(srcCurrent->first, srcCurrent->last);
        if (lastNewContact == nullptr) {
            this->headContactList = newContact; 
        } else {
            lastNewContact->next = newContact; 
        }
        lastNewContact = newContact; 

        Info *srcInfoCurrent = srcCurrent->headInfoList, *lastNewInfo = nullptr;
        while (srcInfoCurrent != nullptr) {
            Info *newInfo = new Info(srcInfoCurrent->name, srcInfoCurrent->value);
            if (lastNewInfo == nullptr) {
                newContact->headInfoList = newInfo; 
            } else {
                lastNewInfo->next = newInfo; 
            }
            lastNewInfo = newInfo; 

            srcInfoCurrent = srcInfoCurrent->next; 
        }

        srcCurrent = srcCurrent->next; 
        count++; 
    }
}


const ContactList &ContactList::operator=(const ContactList &src) {
    if (this == &src) {
        return *this;
    }

    Contact* current = headContactList;
    while (current != nullptr) {
        Info* infoCurrent = current->headInfoList;
        while (infoCurrent != nullptr) {
            Info* tempInfo = infoCurrent;
            infoCurrent = infoCurrent->next;
            delete tempInfo;
        }

        Contact* tempContact = current;
        current = current->next;
        delete tempContact;
    }

    headContactList = nullptr;
    count = 0;

    Contact* srcCurrent = src.headContactList;
    Contact** nextPtr = &headContactList;

    while (srcCurrent != nullptr) {
        *nextPtr = new Contact(srcCurrent->first, srcCurrent->last);
        count++;

        Info* srcInfo = srcCurrent->headInfoList;
        Info** nextInfoPtr = &((*nextPtr)->headInfoList); 
        while (srcInfo != nullptr) {
            *nextInfoPtr = new Info(srcInfo->name, srcInfo->value);
            srcInfo = srcInfo->next;
            nextInfoPtr = &((*nextInfoPtr)->next);
        }

        srcCurrent = srcCurrent->next;
        nextPtr = &((*nextPtr)->next);
    }

    return *this;
}
