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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
struct ucred {int dummy; } ;
struct nfsrv_descript {int nd_repstat; } ;
struct nfsmount {int dummy; } ;
struct nfscllockowner {int dummy; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int EACCES ; 
 int EAUTH ; 
 int NFSERR_DELAY ; 
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  newnfs_setroot (struct ucred*) ; 
 int /*<<< orphan*/  nfs_catnap (int /*<<< orphan*/ ,int,char*) ; 
 int nfsrpc_lock (struct nfsrv_descript*,struct nfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct nfscllockowner*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,short,struct ucred*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
nfscl_trylock(struct nfsmount *nmp, vnode_t vp, u_int8_t *fhp,
    int fhlen, struct nfscllockowner *nlp, int newone, int reclaim,
    u_int64_t off, u_int64_t len, short type, struct ucred *cred, NFSPROC_T *p)
{
	struct nfsrv_descript nfsd, *nd = &nfsd;
	int error;

	do {
		error = nfsrpc_lock(nd, nmp, vp, fhp, fhlen, nlp, newone,
		    reclaim, off, len, type, cred, p, 0);
		if (!error && nd->nd_repstat == NFSERR_DELAY)
			(void) nfs_catnap(PZERO, (int)nd->nd_repstat,
			    "nfstrylck");
	} while (!error && nd->nd_repstat == NFSERR_DELAY);
	if (!error)
		error = nd->nd_repstat;
	if (error == EAUTH || error == EACCES) {
		/* Try again using root credentials */
		newnfs_setroot(cred);
		do {
			error = nfsrpc_lock(nd, nmp, vp, fhp, fhlen, nlp,
			    newone, reclaim, off, len, type, cred, p, 1);
			if (!error && nd->nd_repstat == NFSERR_DELAY)
				(void) nfs_catnap(PZERO, (int)nd->nd_repstat,
				    "nfstrylck");
		} while (!error && nd->nd_repstat == NFSERR_DELAY);
		if (!error)
			error = nd->nd_repstat;
	}
	return (error);
}