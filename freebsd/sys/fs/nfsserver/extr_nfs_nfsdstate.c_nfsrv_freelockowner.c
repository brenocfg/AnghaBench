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
typedef  int /*<<< orphan*/  vnode_t ;
struct nfsstate {scalar_t__ ls_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  srvlockowners; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct nfsstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NFSDSTATE ; 
 int /*<<< orphan*/  free (struct nfsstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ls_hash ; 
 int /*<<< orphan*/  ls_list ; 
 int /*<<< orphan*/  nfsrv_freeallnfslocks (struct nfsstate*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsrv_openpluslock ; 
 int /*<<< orphan*/  nfsrvd_derefcache (scalar_t__) ; 
 TYPE_1__ nfsstatsv1 ; 

__attribute__((used)) static void
nfsrv_freelockowner(struct nfsstate *stp, vnode_t vp, int cansleep,
    NFSPROC_T *p)
{

	LIST_REMOVE(stp, ls_hash);
	LIST_REMOVE(stp, ls_list);
	nfsrv_freeallnfslocks(stp, vp, cansleep, p);
	if (stp->ls_op)
		nfsrvd_derefcache(stp->ls_op);
	free(stp, M_NFSDSTATE);
	nfsstatsv1.srvlockowners--;
	nfsrv_openpluslock--;
}