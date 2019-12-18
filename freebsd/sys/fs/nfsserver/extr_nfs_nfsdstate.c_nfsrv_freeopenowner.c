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
struct nfsstate {scalar_t__ ls_op; int /*<<< orphan*/  ls_open; } ;
struct TYPE_2__ {int /*<<< orphan*/  srvopenowners; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 struct nfsstate* LIST_END (int /*<<< orphan*/ *) ; 
 struct nfsstate* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct nfsstate* LIST_NEXT (struct nfsstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct nfsstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NFSDSTATE ; 
 int /*<<< orphan*/  free (struct nfsstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ls_list ; 
 int /*<<< orphan*/  nfsrv_freeopen (struct nfsstate*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsrv_openpluslock ; 
 int /*<<< orphan*/  nfsrvd_derefcache (scalar_t__) ; 
 TYPE_1__ nfsstatsv1 ; 

__attribute__((used)) static void
nfsrv_freeopenowner(struct nfsstate *stp, int cansleep, NFSPROC_T *p)
{
	struct nfsstate *nstp, *tstp;

	LIST_REMOVE(stp, ls_list);
	/*
	 * Now, free all associated opens.
	 */
	nstp = LIST_FIRST(&stp->ls_open);
	while (nstp != LIST_END(&stp->ls_open)) {
		tstp = nstp;
		nstp = LIST_NEXT(nstp, ls_list);
		(void) nfsrv_freeopen(tstp, NULL, cansleep, p);
	}
	if (stp->ls_op)
		nfsrvd_derefcache(stp->ls_op);
	free(stp, M_NFSDSTATE);
	nfsstatsv1.srvopenowners--;
	nfsrv_openpluslock--;
}