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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  scalar_t__ uint64_t ;
struct nfslockfile {int /*<<< orphan*/  lf_locallock; } ;
struct nfslockconflict {int dummy; } ;
struct nfslock {scalar_t__ lo_end; scalar_t__ lo_first; int /*<<< orphan*/  lo_flags; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 struct nfslock* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct nfslock* LIST_NEXT (struct nfslock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int /*<<< orphan*/  NFSLCK_UNLOCK ; 
 int /*<<< orphan*/  lo_lckowner ; 
 int nfsrv_dolocal (int /*<<< orphan*/ ,struct nfslockfile*,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct nfslockconflict*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfsrv_locallock(vnode_t vp, struct nfslockfile *lfp, int flags,
    uint64_t first, uint64_t end, struct nfslockconflict *cfp, NFSPROC_T *p)
{
	struct nfslock *lop, *nlop;
	int error = 0;

	/* Loop through the list of locks. */
	lop = LIST_FIRST(&lfp->lf_locallock);
	while (first < end && lop != NULL) {
		nlop = LIST_NEXT(lop, lo_lckowner);
		if (first >= lop->lo_end) {
			/* not there yet */
			lop = nlop;
		} else if (first < lop->lo_first) {
			/* new one starts before entry in list */
			if (end <= lop->lo_first) {
				/* no overlap between old and new */
				error = nfsrv_dolocal(vp, lfp, flags,
				    NFSLCK_UNLOCK, first, end, cfp, p);
				if (error != 0)
					break;
				first = end;
			} else {
				/* handle fragment overlapped with new one */
				error = nfsrv_dolocal(vp, lfp, flags,
				    NFSLCK_UNLOCK, first, lop->lo_first, cfp,
				    p);
				if (error != 0)
					break;
				first = lop->lo_first;
			}
		} else {
			/* new one overlaps this entry in list */
			if (end <= lop->lo_end) {
				/* overlaps all of new one */
				error = nfsrv_dolocal(vp, lfp, flags,
				    lop->lo_flags, first, end, cfp, p);
				if (error != 0)
					break;
				first = end;
			} else {
				/* handle fragment overlapped with new one */
				error = nfsrv_dolocal(vp, lfp, flags,
				    lop->lo_flags, first, lop->lo_end, cfp, p);
				if (error != 0)
					break;
				first = lop->lo_end;
				lop = nlop;
			}
		}
	}
	if (first < end && error == 0)
		/* handle fragment past end of list */
		error = nfsrv_dolocal(vp, lfp, flags, NFSLCK_UNLOCK, first,
		    end, cfp, p);

	NFSEXITCODE(error);
	return (error);
}