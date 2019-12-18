#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct attr* first; } ;
typedef  TYPE_1__ uiprivAttrList ;
struct attr {size_t end; size_t start; struct attr* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  attrInsertBefore (TYPE_1__*,struct attr*,struct attr*) ; 
 int /*<<< orphan*/  attrUnlink (TYPE_1__*,struct attr*) ; 

__attribute__((used)) static void attrGrow(uiprivAttrList *alist, struct attr *a, size_t start, size_t end)
{
	struct attr *before;

	// adjusting the end is simple: if it ends before our new end, just set the new end
	if (a->end < end)
		a->end = end;

	// adjusting the start is harder
	// if the start is before our new start, we are done
	// otherwise, we have to move the start back AND reposition the attribute to keep the sorted order
	if (a->start <= start)
		return;
	a->start = start;
	attrUnlink(alist, a);
	for (before = alist->first; before != NULL; before = before->next)
		if (before->start > a->start)
			break;
	attrInsertBefore(alist, a, before);
}