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
struct TYPE_3__ {struct attr* first; struct attr* last; } ;
typedef  TYPE_1__ uiprivAttrList ;
struct attr {struct attr* next; struct attr* prev; } ;

/* Variables and functions */

__attribute__((used)) static void attrInsertBefore(uiprivAttrList *alist, struct attr *a, struct attr *before)
{
	// if the list is empty, this is the first item
	if (alist->first == NULL) {
		alist->first = a;
		alist->last = a;
		return;
	}

	// add to the end
	if (before == NULL) {
		struct attr *oldlast;

		oldlast = alist->last;
		alist->last = a;
		a->prev = oldlast;
		oldlast->next = a;
		return;
	}

	// add to the beginning
	if (before == alist->first) {
		struct attr *oldfirst;

		oldfirst = alist->first;
		alist->first = a;
		oldfirst->prev = a;
		a->next = oldfirst;
		return;
	}

	// add to the middle
	a->prev = before->prev;
	a->next = before;
	before->prev = a;
	a->prev->next = a;
}