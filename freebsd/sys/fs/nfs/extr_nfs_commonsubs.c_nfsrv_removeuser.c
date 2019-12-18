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
struct nfsusrgrp {int /*<<< orphan*/ * lug_cred; int /*<<< orphan*/  lug_namelen; int /*<<< orphan*/  lug_name; int /*<<< orphan*/  lug_gid; int /*<<< orphan*/  lug_uid; } ;
struct nfsrv_lughash {int /*<<< orphan*/  lughead; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_NFSUSERGROUP ; 
 struct nfsrv_lughash* NFSGROUPHASH (int /*<<< orphan*/ ) ; 
 struct nfsrv_lughash* NFSGROUPNAMEHASH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfsrv_lughash* NFSUSERHASH (int /*<<< orphan*/ ) ; 
 struct nfsrv_lughash* NFSUSERNAMEHASH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nfsusrgrp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct nfsusrgrp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lug_namehash ; 
 int /*<<< orphan*/  lug_numhash ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsrv_usercnt ; 

__attribute__((used)) static void
nfsrv_removeuser(struct nfsusrgrp *usrp, int isuser)
{
	struct nfsrv_lughash *hp;

	if (isuser != 0) {
		hp = NFSUSERHASH(usrp->lug_uid);
		mtx_assert(&hp->mtx, MA_OWNED);
		TAILQ_REMOVE(&hp->lughead, usrp, lug_numhash);
		hp = NFSUSERNAMEHASH(usrp->lug_name, usrp->lug_namelen);
		mtx_assert(&hp->mtx, MA_OWNED);
		TAILQ_REMOVE(&hp->lughead, usrp, lug_namehash);
	} else {
		hp = NFSGROUPHASH(usrp->lug_gid);
		mtx_assert(&hp->mtx, MA_OWNED);
		TAILQ_REMOVE(&hp->lughead, usrp, lug_numhash);
		hp = NFSGROUPNAMEHASH(usrp->lug_name, usrp->lug_namelen);
		mtx_assert(&hp->mtx, MA_OWNED);
		TAILQ_REMOVE(&hp->lughead, usrp, lug_namehash);
	}
	atomic_add_int(&nfsrv_usercnt, -1);
	if (usrp->lug_cred != NULL)
		crfree(usrp->lug_cred);
	free(usrp, M_NFSUSERGROUP);
}