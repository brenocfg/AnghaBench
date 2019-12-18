#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct attr* first; } ;
typedef  TYPE_1__ uiprivAttrList ;
struct attr {size_t start; size_t end; struct attr* next; } ;

/* Variables and functions */

void uiprivAttrListInsertCharactersExtendingAttributes(uiprivAttrList *alist, size_t start, size_t count)
{
	struct attr *a;

	for (a = alist->first; a != NULL; a = a->next) {
		if (a->start < start)
			a->start += count;
		else if (a->start == start && start != 0)
			a->start += count;
		if (a->end <= start)
			a->end += count;
	}
}