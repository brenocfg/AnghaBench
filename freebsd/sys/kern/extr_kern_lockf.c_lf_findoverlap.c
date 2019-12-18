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
struct lockf_entry {scalar_t__ lf_start; scalar_t__ lf_end; scalar_t__ lf_owner; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 struct lockf_entry* LIST_NEXT (struct lockf_entry*,int /*<<< orphan*/ ) ; 
 struct lockf_entry* NOLOCKF ; 
 int OTHERS ; 
 int SELF ; 
 int /*<<< orphan*/  lf_link ; 
 int /*<<< orphan*/  lf_print (char*,struct lockf_entry*) ; 
 int lockf_debug ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
lf_findoverlap(struct lockf_entry **overlap, struct lockf_entry *lock, int type)
{
	struct lockf_entry *lf;
	off_t start, end;
	int res;

	if ((*overlap) == NOLOCKF) {
		return (0);
	}
#ifdef LOCKF_DEBUG
	if (lockf_debug & 2)
		lf_print("lf_findoverlap: looking for overlap in", lock);
#endif /* LOCKF_DEBUG */
	start = lock->lf_start;
	end = lock->lf_end;
	res = 0;
	while (*overlap) {
		lf = *overlap;
		if (lf->lf_start > end)
			break;
		if (((type & SELF) && lf->lf_owner != lock->lf_owner) ||
		    ((type & OTHERS) && lf->lf_owner == lock->lf_owner)) {
			*overlap = LIST_NEXT(lf, lf_link);
			continue;
		}
#ifdef LOCKF_DEBUG
		if (lockf_debug & 2)
			lf_print("\tchecking", lf);
#endif /* LOCKF_DEBUG */
		/*
		 * OK, check for overlap
		 *
		 * Six cases:
		 *	0) no overlap
		 *	1) overlap == lock
		 *	2) overlap contains lock
		 *	3) lock contains overlap
		 *	4) overlap starts before lock
		 *	5) overlap ends after lock
		 */
		if (start > lf->lf_end) {
			/* Case 0 */
#ifdef LOCKF_DEBUG
			if (lockf_debug & 2)
				printf("no overlap\n");
#endif /* LOCKF_DEBUG */
			*overlap = LIST_NEXT(lf, lf_link);
			continue;
		}
		if (lf->lf_start == start && lf->lf_end == end) {
			/* Case 1 */
#ifdef LOCKF_DEBUG
			if (lockf_debug & 2)
				printf("overlap == lock\n");
#endif /* LOCKF_DEBUG */
			res = 1;
			break;
		}
		if (lf->lf_start <= start && lf->lf_end >= end) {
			/* Case 2 */
#ifdef LOCKF_DEBUG
			if (lockf_debug & 2)
				printf("overlap contains lock\n");
#endif /* LOCKF_DEBUG */
			res = 2;
			break;
		}
		if (start <= lf->lf_start && end >= lf->lf_end) {
			/* Case 3 */
#ifdef LOCKF_DEBUG
			if (lockf_debug & 2)
				printf("lock contains overlap\n");
#endif /* LOCKF_DEBUG */
			res = 3;
			break;
		}
		if (lf->lf_start < start && lf->lf_end >= start) {
			/* Case 4 */
#ifdef LOCKF_DEBUG
			if (lockf_debug & 2)
				printf("overlap starts before lock\n");
#endif /* LOCKF_DEBUG */
			res = 4;
			break;
		}
		if (lf->lf_start > start && lf->lf_end > end) {
			/* Case 5 */
#ifdef LOCKF_DEBUG
			if (lockf_debug & 2)
				printf("overlap ends after lock\n");
#endif /* LOCKF_DEBUG */
			res = 5;
			break;
		}
		panic("lf_findoverlap: default");
	}
	return (res);
}