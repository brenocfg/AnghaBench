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
typedef  int /*<<< orphan*/  uiprivAttrList ;
struct attr {size_t start; size_t end; struct attr* next; } ;

/* Variables and functions */
 struct attr* attrDelete (int /*<<< orphan*/ *,struct attr*) ; 
 int /*<<< orphan*/  attrRangeIntersect (struct attr*,size_t*,size_t*) ; 

__attribute__((used)) static struct attr *attrDeleteRange(uiprivAttrList *alist, struct attr *a, size_t start, size_t end)
{
	size_t ostart, oend;
	size_t count;

	ostart = start;
	oend = end;
	count = oend - ostart;

	if (!attrRangeIntersect(a, &start, &end)) {
		// out of range
		// adjust if necessary
		if (a->start >= ostart)
			a->start -= count;
		if (a->end >= oend)
			a->end -= count;
		return a->next;
	}

	// just outright delete the attribute?
	// the inequalities handle attributes entirely inside the range
	// if both are equal, the attribute's range is equal to the range
	if (a->start >= start && a->end <= end)
		return attrDelete(alist, a);

	// only chop off the start or end?
	if (a->start == start) {			// chop off the start
		// if we weren't adjusting positions this would just be setting a->start to end
		// but since this is deleting from the start, we need to adjust both by count
		a->start = end - count;
		a->end -= count;
		return a->next;
	}
	if (a->end == end) {				// chop off the end
		// a->start is already good
		a->end = start;
		return a->next;
	}

	// in this case, the deleted range is inside the attribute
	// we can clear it by just removing count from a->end
	a->end -= count;
	return a->next;
}