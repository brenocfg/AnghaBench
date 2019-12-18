#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_3__ {int ex_flags; } ;
struct nfsex_args {int /*<<< orphan*/ * fspec; TYPE_1__ export; } ;
struct nameidata {int /*<<< orphan*/  ni_vp; } ;
typedef  int /*<<< orphan*/  fhandle_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  nfsrvfh_data; int /*<<< orphan*/  nfsrvfh_len; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  FOLLOW ; 
 int /*<<< orphan*/  LOOKUP ; 
 int MNT_DELEXPORT ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct thread*) ; 
 int /*<<< orphan*/  NFSBCOPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int /*<<< orphan*/  NFSX_MYFH ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int namei (struct nameidata*) ; 
 TYPE_2__ nfs_rootfh ; 
 int nfs_rootfhset ; 
 int /*<<< orphan*/  nfsv4root_mnt ; 
 int nfsvno_getfh (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct thread*) ; 
 int vfs_export (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ ) ; 

int
nfsrv_v4rootexport(void *argp, struct ucred *cred, struct thread *p)
{
	struct nfsex_args *nfsexargp = (struct nfsex_args *)argp;
	int error = 0;
	struct nameidata nd;
	fhandle_t fh;

	error = vfs_export(&nfsv4root_mnt, &nfsexargp->export);
	if ((nfsexargp->export.ex_flags & MNT_DELEXPORT) != 0)
		nfs_rootfhset = 0;
	else if (error == 0) {
		if (nfsexargp->fspec == NULL) {
			error = EPERM;
			goto out;
		}
		/*
		 * If fspec != NULL, this is the v4root path.
		 */
		NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE,
		    nfsexargp->fspec, p);
		if ((error = namei(&nd)) != 0)
			goto out;
		error = nfsvno_getfh(nd.ni_vp, &fh, p);
		vrele(nd.ni_vp);
		if (!error) {
			nfs_rootfh.nfsrvfh_len = NFSX_MYFH;
			NFSBCOPY((caddr_t)&fh,
			    nfs_rootfh.nfsrvfh_data,
			    sizeof (fhandle_t));
			nfs_rootfhset = 1;
		}
	}

out:
	NFSEXITCODE(error);
	return (error);
}