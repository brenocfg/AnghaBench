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
struct nfsstate {int /*<<< orphan*/  ls_lock; } ;
struct nfslockfile {int /*<<< orphan*/  lf_locallock; } ;
struct nfslock {int lo_flags; scalar_t__ lo_end; scalar_t__ lo_first; struct nfslockfile* lo_lfp; struct nfsstate* lo_stp; } ;

/* Variables and functions */
 struct nfslock* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct nfslock* LIST_NEXT (struct nfslock*,int /*<<< orphan*/ ) ; 
 int NFSLCK_UNLOCK ; 
 int /*<<< orphan*/  lo_lckowner ; 
 int /*<<< orphan*/  nfsrv_freenfslock (struct nfslock*) ; 
 int /*<<< orphan*/  nfsrv_insertlock (struct nfslock*,struct nfslock*,struct nfsstate*,struct nfslockfile*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
nfsrv_updatelock(struct nfsstate *stp, struct nfslock **new_lopp,
    struct nfslock **other_lopp, struct nfslockfile *lfp)
{
	struct nfslock *new_lop = *new_lopp;
	struct nfslock *lop, *tlop, *ilop;
	struct nfslock *other_lop = *other_lopp;
	int unlock = 0, myfile = 0;
	u_int64_t tmp;

	/*
	 * Work down the list until the lock is merged.
	 */
	if (new_lop->lo_flags & NFSLCK_UNLOCK)
		unlock = 1;
	if (stp != NULL) {
		ilop = (struct nfslock *)stp;
		lop = LIST_FIRST(&stp->ls_lock);
	} else {
		ilop = (struct nfslock *)lfp;
		lop = LIST_FIRST(&lfp->lf_locallock);
	}
	while (lop != NULL) {
	    /*
	     * Only check locks for this file that aren't before the start of
	     * new lock's range.
	     */
	    if (lop->lo_lfp == lfp) {
	      myfile = 1;
	      if (lop->lo_end >= new_lop->lo_first) {
		if (new_lop->lo_end < lop->lo_first) {
			/*
			 * If the new lock ends before the start of the
			 * current lock's range, no merge, just insert
			 * the new lock.
			 */
			break;
		}
		if (new_lop->lo_flags == lop->lo_flags ||
		    (new_lop->lo_first <= lop->lo_first &&
		     new_lop->lo_end >= lop->lo_end)) {
			/*
			 * This lock can be absorbed by the new lock/unlock.
			 * This happens when it covers the entire range
			 * of the old lock or is contiguous
			 * with the old lock and is of the same type or an
			 * unlock.
			 */
			if (lop->lo_first < new_lop->lo_first)
				new_lop->lo_first = lop->lo_first;
			if (lop->lo_end > new_lop->lo_end)
				new_lop->lo_end = lop->lo_end;
			tlop = lop;
			lop = LIST_NEXT(lop, lo_lckowner);
			nfsrv_freenfslock(tlop);
			continue;
		}

		/*
		 * All these cases are for contiguous locks that are not the
		 * same type, so they can't be merged.
		 */
		if (new_lop->lo_first <= lop->lo_first) {
			/*
			 * This case is where the new lock overlaps with the
			 * first part of the old lock. Move the start of the
			 * old lock to just past the end of the new lock. The
			 * new lock will be inserted in front of the old, since
			 * ilop hasn't been updated. (We are done now.)
			 */
			lop->lo_first = new_lop->lo_end;
			break;
		}
		if (new_lop->lo_end >= lop->lo_end) {
			/*
			 * This case is where the new lock overlaps with the
			 * end of the old lock's range. Move the old lock's
			 * end to just before the new lock's first and insert
			 * the new lock after the old lock.
			 * Might not be done yet, since the new lock could
			 * overlap further locks with higher ranges.
			 */
			lop->lo_end = new_lop->lo_first;
			ilop = lop;
			lop = LIST_NEXT(lop, lo_lckowner);
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
		 * new_lop->lo_flags any longer.
		 */
		tmp = new_lop->lo_first;
		if (other_lop == NULL) {
			if (!unlock)
				panic("nfsd srv update unlock");
			other_lop = new_lop;
			*new_lopp = NULL;
		}
		other_lop->lo_first = new_lop->lo_end;
		other_lop->lo_end = lop->lo_end;
		other_lop->lo_flags = lop->lo_flags;
		other_lop->lo_stp = stp;
		other_lop->lo_lfp = lfp;
		lop->lo_end = tmp;
		nfsrv_insertlock(other_lop, lop, stp, lfp);
		*other_lopp = NULL;
		ilop = lop;
		break;
	      }
	    }
	    ilop = lop;
	    lop = LIST_NEXT(lop, lo_lckowner);
	    if (myfile && (lop == NULL || lop->lo_lfp != lfp))
		break;
	}

	/*
	 * Insert the new lock in the list at the appropriate place.
	 */
	if (!unlock) {
		nfsrv_insertlock(new_lop, ilop, stp, lfp);
		*new_lopp = NULL;
	}
}