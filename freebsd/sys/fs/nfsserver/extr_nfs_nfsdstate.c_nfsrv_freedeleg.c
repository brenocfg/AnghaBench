#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfsstate {int ls_flags; struct nfslockfile* ls_lfp; } ;
struct nfslockfile {scalar_t__ lf_usecount; int /*<<< orphan*/  lf_locallock_lck; int /*<<< orphan*/  lf_rollback; int /*<<< orphan*/  lf_locallock; int /*<<< orphan*/  lf_deleg; int /*<<< orphan*/  lf_lock; int /*<<< orphan*/  lf_open; } ;
struct TYPE_2__ {int /*<<< orphan*/  srvdelegates; } ;

/* Variables and functions */
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct nfsstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NFSDSTATE ; 
 int NFSLCK_DELEGWRITE ; 
 int /*<<< orphan*/  free (struct nfsstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ls_file ; 
 int /*<<< orphan*/  ls_hash ; 
 int /*<<< orphan*/  ls_list ; 
 int /*<<< orphan*/  nfsrv_delegatecnt ; 
 int /*<<< orphan*/  nfsrv_freenfslockfile (struct nfslockfile*) ; 
 int /*<<< orphan*/  nfsrv_openpluslock ; 
 int /*<<< orphan*/  nfsrv_writedelegcnt ; 
 TYPE_1__ nfsstatsv1 ; 
 scalar_t__ nfsv4_testlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfsrv_freedeleg(struct nfsstate *stp)
{
	struct nfslockfile *lfp;

	LIST_REMOVE(stp, ls_hash);
	LIST_REMOVE(stp, ls_list);
	LIST_REMOVE(stp, ls_file);
	if ((stp->ls_flags & NFSLCK_DELEGWRITE) != 0)
		nfsrv_writedelegcnt--;
	lfp = stp->ls_lfp;
	if (LIST_EMPTY(&lfp->lf_open) &&
	    LIST_EMPTY(&lfp->lf_lock) && LIST_EMPTY(&lfp->lf_deleg) &&
	    LIST_EMPTY(&lfp->lf_locallock) && LIST_EMPTY(&lfp->lf_rollback) &&
	    lfp->lf_usecount == 0 &&
	    nfsv4_testlock(&lfp->lf_locallock_lck) == 0)
		nfsrv_freenfslockfile(lfp);
	free(stp, M_NFSDSTATE);
	nfsstatsv1.srvdelegates--;
	nfsrv_openpluslock--;
	nfsrv_delegatecnt--;
}