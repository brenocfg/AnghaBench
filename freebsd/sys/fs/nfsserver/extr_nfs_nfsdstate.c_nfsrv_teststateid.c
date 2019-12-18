#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_quad_t ;
struct TYPE_5__ {int /*<<< orphan*/  seqid; } ;
struct nfsstate {TYPE_1__ ls_stateid; } ;
struct nfsrv_descript {int dummy; } ;
struct nfsclient {int dummy; } ;
struct TYPE_6__ {scalar_t__ seqid; } ;
typedef  TYPE_2__ nfsv4stateid_t ;
typedef  int /*<<< orphan*/  nfsquad_t ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int /*<<< orphan*/  CLOPS_RENEW ; 
 int NFSERR_OLDSTATEID ; 
 int /*<<< orphan*/  NFSLOCKSTATE () ; 
 int /*<<< orphan*/  NFSUNLOCKSTATE () ; 
 scalar_t__ SEQ_LT (scalar_t__,int /*<<< orphan*/ ) ; 
 int nfsrv_getclient (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsclient**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfsrv_descript*,int /*<<< orphan*/ *) ; 
 int nfsrv_getstate (struct nfsclient*,TYPE_2__*,int /*<<< orphan*/ ,struct nfsstate**) ; 

int
nfsrv_teststateid(struct nfsrv_descript *nd, nfsv4stateid_t *stateidp,
    NFSPROC_T *p)
{
	struct nfsclient *clp;
	struct nfsstate *stp;
	int error;

	NFSLOCKSTATE();
	/*
	 * Look up the stateid
	 */
	error = nfsrv_getclient((nfsquad_t)((u_quad_t)0), CLOPS_RENEW, &clp,
	    NULL, (nfsquad_t)((u_quad_t)0), 0, nd, p);
	if (error == 0)
		error = nfsrv_getstate(clp, stateidp, 0, &stp);
	if (error == 0 && stateidp->seqid != 0 &&
	    SEQ_LT(stateidp->seqid, stp->ls_stateid.seqid))
		error = NFSERR_OLDSTATEID;
	NFSUNLOCKSTATE();
	return (error);
}