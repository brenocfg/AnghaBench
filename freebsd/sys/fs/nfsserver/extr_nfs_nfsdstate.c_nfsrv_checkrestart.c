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
typedef  int u_int32_t ;
struct TYPE_5__ {scalar_t__* other; } ;
typedef  TYPE_1__ nfsv4stateid_t ;
struct TYPE_6__ {scalar_t__* lval; } ;
typedef  TYPE_2__ nfsquad_t ;

/* Variables and functions */
 int NFSERR_STALECLIENTID ; 
 int NFSERR_STALESTATEID ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int NFSLCK_CHECK ; 
 int NFSLCK_DELEGPURGE ; 
 int NFSLCK_OPEN ; 
 int NFSLCK_RELEASE ; 
 int NFSLCK_TEST ; 
 int /*<<< orphan*/  NFSLOCKSTATE () ; 
 int /*<<< orphan*/  NFSUNLOCKSTATE () ; 
 int nfsrv_checkgrace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ nfsrvboottime ; 

__attribute__((used)) static int
nfsrv_checkrestart(nfsquad_t clientid, u_int32_t flags,
    nfsv4stateid_t *stateidp, int specialid)
{
	int ret = 0;

	/*
	 * First check for a server restart. Open, LockT, ReleaseLockOwner
	 * and DelegPurge have a clientid, the rest a stateid.
	 */
	if (flags &
	    (NFSLCK_OPEN | NFSLCK_TEST | NFSLCK_RELEASE | NFSLCK_DELEGPURGE)) {
		if (clientid.lval[0] != nfsrvboottime) {
			ret = NFSERR_STALECLIENTID;
			goto out;
		}
	} else if (stateidp->other[0] != nfsrvboottime &&
		specialid == 0) {
		ret = NFSERR_STALESTATEID;
		goto out;
	}

	/*
	 * Read, Write, Setattr and LockT can return NFSERR_GRACE and do
	 * not use a lock/open owner seqid#, so the check can be done now.
	 * (The others will be checked, as required, later.)
	 */
	if (!(flags & (NFSLCK_CHECK | NFSLCK_TEST)))
		goto out;

	NFSLOCKSTATE();
	ret = nfsrv_checkgrace(NULL, NULL, flags);
	NFSUNLOCKSTATE();

out:
	NFSEXITCODE(ret);
	return (ret);
}