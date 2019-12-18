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
typedef  scalar_t__ u_int64_t ;
struct nfscllockowner {int /*<<< orphan*/  nfsl_lock; } ;
struct nfscllock {scalar_t__ nfslo_type; scalar_t__ nfslo_end; scalar_t__ nfslo_first; } ;

/* Variables and functions */
 scalar_t__ F_UNLCK ; 
 struct nfscllock* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct nfscllock* LIST_NEXT (struct nfscllock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfscl_freelock (struct nfscllock*,int) ; 
 int /*<<< orphan*/  nfscl_insertlock (struct nfscllockowner*,struct nfscllock*,struct nfscllock*,int) ; 
 int /*<<< orphan*/  nfslo_list ; 

__attribute__((used)) static int
nfscl_updatelock(struct nfscllockowner *lp, struct nfscllock **new_lopp,
    struct nfscllock **other_lopp, int local)
{
	struct nfscllock *new_lop = *new_lopp;
	struct nfscllock *lop, *tlop, *ilop;
	struct nfscllock *other_lop;
	int unlock = 0, modified = 0;
	u_int64_t tmp;

	/*
	 * Work down the list until the lock is merged.
	 */
	if (new_lop->nfslo_type == F_UNLCK)
		unlock = 1;
	ilop = (struct nfscllock *)lp;
	lop = LIST_FIRST(&lp->nfsl_lock);
	while (lop != NULL) {
	    /*
	     * Only check locks for this file that aren't before the start of
	     * new lock's range.
	     */
	    if (lop->nfslo_end >= new_lop->nfslo_first) {
		if (new_lop->nfslo_end < lop->nfslo_first) {
		    /*
		     * If the new lock ends before the start of the
		     * current lock's range, no merge, just insert
		     * the new lock.
		     */
		    break;
		}
		if (new_lop->nfslo_type == lop->nfslo_type ||
		    (new_lop->nfslo_first <= lop->nfslo_first &&
		     new_lop->nfslo_end >= lop->nfslo_end)) {
		    /*
		     * This lock can be absorbed by the new lock/unlock.
		     * This happens when it covers the entire range
		     * of the old lock or is contiguous
		     * with the old lock and is of the same type or an
		     * unlock.
		     */
		    if (new_lop->nfslo_type != lop->nfslo_type ||
			new_lop->nfslo_first != lop->nfslo_first ||
			new_lop->nfslo_end != lop->nfslo_end)
			modified = 1;
		    if (lop->nfslo_first < new_lop->nfslo_first)
			new_lop->nfslo_first = lop->nfslo_first;
		    if (lop->nfslo_end > new_lop->nfslo_end)
			new_lop->nfslo_end = lop->nfslo_end;
		    tlop = lop;
		    lop = LIST_NEXT(lop, nfslo_list);
		    nfscl_freelock(tlop, local);
		    continue;
		}

		/*
		 * All these cases are for contiguous locks that are not the
		 * same type, so they can't be merged.
		 */
		if (new_lop->nfslo_first <= lop->nfslo_first) {
		    /*
		     * This case is where the new lock overlaps with the
		     * first part of the old lock. Move the start of the
		     * old lock to just past the end of the new lock. The
		     * new lock will be inserted in front of the old, since
		     * ilop hasn't been updated. (We are done now.)
		     */
		    if (lop->nfslo_first != new_lop->nfslo_end) {
			lop->nfslo_first = new_lop->nfslo_end;
			modified = 1;
		    }
		    break;
		}
		if (new_lop->nfslo_end >= lop->nfslo_end) {
		    /*
		     * This case is where the new lock overlaps with the
		     * end of the old lock's range. Move the old lock's
		     * end to just before the new lock's first and insert
		     * the new lock after the old lock.
		     * Might not be done yet, since the new lock could
		     * overlap further locks with higher ranges.
		     */
		    if (lop->nfslo_end != new_lop->nfslo_first) {
			lop->nfslo_end = new_lop->nfslo_first;
			modified = 1;
		    }
		    ilop = lop;
		    lop = LIST_NEXT(lop, nfslo_list);
		    continue;
		}
		/*
		 * The final case is where the new lock's range is in the
		 * middle of the current lock's and splits the current lock
		 * up. Use *other_lopp to handle the second part of the
		 * split old lock range. (We are done now.)
		 * For unlock, we use new_lop as other_lop and tmp, since
		 * other_lop and new_lop are the same for this case.
		 * We noted the unlock case above, so we don't need
		 * new_lop->nfslo_type any longer.
		 */
		tmp = new_lop->nfslo_first;
		if (unlock) {
		    other_lop = new_lop;
		    *new_lopp = NULL;
		} else {
		    other_lop = *other_lopp;
		    *other_lopp = NULL;
		}
		other_lop->nfslo_first = new_lop->nfslo_end;
		other_lop->nfslo_end = lop->nfslo_end;
		other_lop->nfslo_type = lop->nfslo_type;
		lop->nfslo_end = tmp;
		nfscl_insertlock(lp, other_lop, lop, local);
		ilop = lop;
		modified = 1;
		break;
	    }
	    ilop = lop;
	    lop = LIST_NEXT(lop, nfslo_list);
	    if (lop == NULL)
		break;
	}

	/*
	 * Insert the new lock in the list at the appropriate place.
	 */
	if (!unlock) {
		nfscl_insertlock(lp, new_lop, ilop, local);
		*new_lopp = NULL;
		modified = 1;
	}
	return (modified);
}