#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct proxy_entry {int rule_index; struct proxy_entry* next; struct proxy_entry* last; struct libalias* la; } ;
struct libalias {struct proxy_entry* proxyList; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 

void
RuleAdd(struct libalias *la, struct proxy_entry *entry)
{
	int rule_index;
	struct proxy_entry *ptr;
	struct proxy_entry *ptr_last;

	LIBALIAS_LOCK_ASSERT(la);

	entry->la = la;
	if (la->proxyList == NULL) {
		la->proxyList = entry;
		entry->last = NULL;
		entry->next = NULL;
		return;
	}

	rule_index = entry->rule_index;
	ptr = la->proxyList;
	ptr_last = NULL;
	while (ptr != NULL) {
		if (ptr->rule_index >= rule_index) {
			if (ptr_last == NULL) {
				entry->next = la->proxyList;
				entry->last = NULL;
				la->proxyList->last = entry;
				la->proxyList = entry;
				return;
			}
			ptr_last->next = entry;
			ptr->last = entry;
			entry->last = ptr->last;
			entry->next = ptr;
			return;
		}
		ptr_last = ptr;
		ptr = ptr->next;
	}

	ptr_last->next = entry;
	entry->last = ptr_last;
	entry->next = NULL;
}