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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ucred {int dummy; } ;
struct nfsmount {int dummy; } ;
struct nfsclopen {int dummy; } ;
struct nfscldeleg {int dummy; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int EACCES ; 
 int EAUTH ; 
 int NFSERR_DELAY ; 
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  newnfs_setroot (struct ucred*) ; 
 int /*<<< orphan*/  nfs_catnap (int /*<<< orphan*/ ,int,char*) ; 
 int nfsrpc_openrpc (struct nfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct nfsclopen*,int /*<<< orphan*/ *,int,struct nfscldeleg**,int,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfscl_tryopen(struct nfsmount *nmp, vnode_t vp, u_int8_t *fhp, int fhlen,
    u_int8_t *newfhp, int newfhlen, u_int32_t mode, struct nfsclopen *op,
    u_int8_t *name, int namelen, struct nfscldeleg **ndpp,
    int reclaim, u_int32_t delegtype, struct ucred *cred, NFSPROC_T *p)
{
	int error;

	do {
		error = nfsrpc_openrpc(nmp, vp, fhp, fhlen, newfhp, newfhlen,
		    mode, op, name, namelen, ndpp, reclaim, delegtype, cred, p,
		    0, 0);
		if (error == NFSERR_DELAY)
			(void) nfs_catnap(PZERO, error, "nfstryop");
	} while (error == NFSERR_DELAY);
	if (error == EAUTH || error == EACCES) {
		/* Try again using system credentials */
		newnfs_setroot(cred);
		do {
		    error = nfsrpc_openrpc(nmp, vp, fhp, fhlen, newfhp,
			newfhlen, mode, op, name, namelen, ndpp, reclaim,
			delegtype, cred, p, 1, 0);
		    if (error == NFSERR_DELAY)
			(void) nfs_catnap(PZERO, error, "nfstryop");
		} while (error == NFSERR_DELAY);
	}
	return (error);
}