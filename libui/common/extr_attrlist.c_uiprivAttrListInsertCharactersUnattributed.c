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
struct attr {size_t start; size_t end; struct attr* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  attrHasPos (struct attr*,size_t) ; 
 int /*<<< orphan*/  attrInsertBefore (TYPE_1__*,struct attr*,struct attr*) ; 
 struct attr* attrSplitAt (TYPE_1__*,struct attr*,size_t) ; 

void uiprivAttrListInsertCharactersUnattributed(uiprivAttrList *alist, size_t start, size_t count)
{
	struct attr *a;
	struct attr *tails = NULL;

	// every attribute before the insertion point can either cross into the insertion point or not
	// if it does, we need to split that attribute apart at the insertion point, keeping only the old attribute in place, adjusting the new tail, and preparing it for being re-added later
	for (a = alist->first; a != NULL; a = a->next) {
		struct attr *tail;

		// stop once we get to the insertion point
		if (a->start >= start)
			break;
		// only do something if overlapping
		if (!attrHasPos(a, start))
			continue;

		tail = attrSplitAt(alist, a, start);
		// adjust the new tail for the insertion
		tail->start += count;
		tail->end += count;
		// and queue it for re-adding later
		// we can safely use tails as if it was singly-linked since it's just a temporary list; we properly merge them back in below and they'll be doubly-linked again then
		// TODO actually we could probably save some time by making then doubly-linked now and adding them in one fell swoop, but that would make things a bit more complicated...
		tail->next = tails;
		tails = tail;
	}

	// at this point in the attribute list, we are at or after the insertion point
	// all the split-apart attributes will be at the insertion point
	// therefore, we can just add them all back now, and the list will still be sorted correctly
	while (tails != NULL) {
		struct attr *next;

		// make all the links NULL before insertion, just to be safe
		next = tails->next;
		tails->next = NULL;
		attrInsertBefore(alist, tails, a);
		tails = next;
	}

	// every remaining attribute will be either at or after the insertion point
	// we just need to move them ahead
	for (; a != NULL; a = a->next) {
		a->start += count;
		a->end += count;
	}
}