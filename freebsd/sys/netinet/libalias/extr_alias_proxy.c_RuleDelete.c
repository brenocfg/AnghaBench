#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct proxy_entry {TYPE_1__* last; TYPE_2__* next; struct libalias* la; } ;
struct libalias {TYPE_2__* proxyList; } ;
struct TYPE_4__ {TYPE_1__* last; } ;
struct TYPE_3__ {TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int /*<<< orphan*/  free (struct proxy_entry*) ; 

__attribute__((used)) static void
RuleDelete(struct proxy_entry *entry)
{
	struct libalias *la;

	la = entry->la;
	LIBALIAS_LOCK_ASSERT(la);
	if (entry->last != NULL)
		entry->last->next = entry->next;
	else
		la->proxyList = entry->next;

	if (entry->next != NULL)
		entry->next->last = entry->last;

	free(entry);
}