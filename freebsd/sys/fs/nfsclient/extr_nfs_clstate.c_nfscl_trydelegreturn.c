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
struct ucred {int dummy; } ;
struct nfsmount {int dummy; } ;
struct nfscldeleg {int dummy; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int EACCES ; 
 int EAUTH ; 
 int NFSERR_DELAY ; 
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  newnfs_setroot (struct ucred*) ; 
 int /*<<< orphan*/  nfs_catnap (int /*<<< orphan*/ ,int,char*) ; 
 int nfsrpc_delegreturn (struct nfscldeleg*,struct ucred*,struct nfsmount*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
nfscl_trydelegreturn(struct nfscldeleg *dp, struct ucred *cred,
    struct nfsmount *nmp, NFSPROC_T *p)
{
	int error;

	do {
		error = nfsrpc_delegreturn(dp, cred, nmp, p, 0);
		if (error == NFSERR_DELAY)
			(void) nfs_catnap(PZERO, error, "nfstrydp");
	} while (error == NFSERR_DELAY);
	if (error == EAUTH || error == EACCES) {
		/* Try again using system credentials */
		newnfs_setroot(cred);
		do {
			error = nfsrpc_delegreturn(dp, cred, nmp, p, 1);
			if (error == NFSERR_DELAY)
				(void) nfs_catnap(PZERO, error, "nfstrydp");
		} while (error == NFSERR_DELAY);
	}
	return (error);
}