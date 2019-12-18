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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nameidata {int /*<<< orphan*/  ni_vp; } ;
struct chroot_args {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int AUDITVNODE1 ; 
 int FOLLOW ; 
 int LOCKLEAF ; 
 int LOCKSHARED ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  PRIV_VFS_CHROOT ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int change_dir (int /*<<< orphan*/ ,struct thread*) ; 
 int mac_vnode_check_chroot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int namei (struct nameidata*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int pwd_chroot (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ ) ; 

int
sys_chroot(struct thread *td, struct chroot_args *uap)
{
	struct nameidata nd;
	int error;

	error = priv_check(td, PRIV_VFS_CHROOT);
	if (error != 0)
		return (error);
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKSHARED | LOCKLEAF | AUDITVNODE1,
	    UIO_USERSPACE, uap->path, td);
	error = namei(&nd);
	if (error != 0)
		goto error;
	error = change_dir(nd.ni_vp, td);
	if (error != 0)
		goto e_vunlock;
#ifdef MAC
	error = mac_vnode_check_chroot(td->td_ucred, nd.ni_vp);
	if (error != 0)
		goto e_vunlock;
#endif
	VOP_UNLOCK(nd.ni_vp, 0);
	error = pwd_chroot(td, nd.ni_vp);
	vrele(nd.ni_vp);
	NDFREE(&nd, NDF_ONLY_PNBUF);
	return (error);
e_vunlock:
	vput(nd.ni_vp);
error:
	NDFREE(&nd, NDF_ONLY_PNBUF);
	return (error);
}