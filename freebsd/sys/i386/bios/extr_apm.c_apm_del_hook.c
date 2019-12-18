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
struct apmhook {struct apmhook* ah_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
apm_del_hook(struct apmhook **list, struct apmhook *ah)
{
	struct apmhook *p, *prev;

	prev = NULL;
	for (p = *list; p != NULL; prev = p, p = p->ah_next)
		if (p == ah)
			goto deleteit;
	panic("Tried to delete unregistered apm_hook.");
	return;
deleteit:
	if (prev != NULL)
		prev->ah_next = p->ah_next;
	else
		*list = p->ah_next;
}