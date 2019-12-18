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
typedef  scalar_t__ uiAttributeType ;
struct attr {size_t start; struct attr* next; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 struct attr* attrDropRange (TYPE_1__*,struct attr*,size_t,size_t,struct attr**) ; 
 int /*<<< orphan*/  attrInsertBefore (TYPE_1__*,struct attr*,struct attr*) ; 
 int /*<<< orphan*/  attrRangeIntersect (struct attr*,size_t*,size_t*) ; 
 scalar_t__ uiAttributeGetType (int /*<<< orphan*/ ) ; 

void uiprivAttrListRemoveAttribute(uiprivAttrList *alist, uiAttributeType type, size_t start, size_t end)
{
	struct attr *a;
	struct attr *tails = NULL;		// see uiprivAttrListInsertCharactersUnattributed() above
	struct attr *tailsAt = NULL;

	a = alist->first;
	while (a != NULL) {
		size_t lstart, lend;
		struct attr *tail;

		// this defines where to re-attach the tails
		// (all the tails will have their start at end, so we can just insert them all before tailsAt)
		if (a->start >= end) {
			tailsAt = a;
			// and at this point we're done, so
			break;
		}
		if (uiAttributeGetType(a->val) != type)
			goto next;
		lstart = start;
		lend = end;
		if (!attrRangeIntersect(a, &lstart, &lend))
			goto next;
		a = attrDropRange(alist, a, start, end, &tail);
		if (tail != NULL) {
			tail->next = tails;
			tails = tail;
		}
		continue;

	next:
		a = a->next;
	}

	while (tails != NULL) {
		struct attr *next;

		// make all the links NULL before insertion, just to be safe
		next = tails->next;
		tails->next = NULL;
		attrInsertBefore(alist, tails, a);
		tails = next;
	}
}