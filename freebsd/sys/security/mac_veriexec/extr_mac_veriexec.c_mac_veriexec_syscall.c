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
struct vattr {int va_mode; } ;
struct thread {int /*<<< orphan*/  td_ucred; int /*<<< orphan*/  td_proc; } ;
struct nameidata {int /*<<< orphan*/  ni_vp; } ;
struct image_params {int /*<<< orphan*/  vp; struct vattr* attr; int /*<<< orphan*/  proc; } ;
struct file {int /*<<< orphan*/  f_vnode; int /*<<< orphan*/  f_type; } ;
typedef  int /*<<< orphan*/  img ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int AUDITVNODE1 ; 
 int /*<<< orphan*/  CAP_READ ; 
 int /*<<< orphan*/  DTYPE_VNODE ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int FOLLOW ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LOCKLEAF ; 
 int LOCKSHARED ; 
 int /*<<< orphan*/  LOOKUP ; 
#define  MAC_VERIEXEC_CHECK_FD_SYSCALL 129 
#define  MAC_VERIEXEC_CHECK_PATH_SYSCALL 128 
 int /*<<< orphan*/  MAC_VERIEXEC_DBG (int,char*,int,...) ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,struct thread*) ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int VOP_GETATTR (int /*<<< orphan*/ ,struct vattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VVERIFY ; 
 int /*<<< orphan*/  bzero (struct image_params*,int) ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int getvnode (struct thread*,uintptr_t,int /*<<< orphan*/ ,struct file**) ; 
 int mac_veriexec_check_vp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mac_veriexec_fingerprint_check_image (struct image_params*,int,struct thread*) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  vn_lock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vput (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mac_veriexec_syscall(struct thread *td, int call, void *arg)
{
	struct image_params img;
	struct nameidata nd;
	cap_rights_t rights;
	struct vattr va;
	struct file *fp;
	int error;

	switch (call) {
	case MAC_VERIEXEC_CHECK_FD_SYSCALL:
		/* Get the vnode associated with the file descriptor passed */
		error = getvnode(td, (uintptr_t) arg, cap_rights_init(&rights,
		    CAP_READ), &fp);
		if (error)
			return (error);
		if (fp->f_type != DTYPE_VNODE) {
			MAC_VERIEXEC_DBG(3, "MAC_VERIEXEC_CHECK_SYSCALL: "
			    "file is not vnode type (type=0x%x)",
			    fp->f_type);
			error = EINVAL;
			goto cleanup_file;
		}

		/*
		 * setup the bits of image_params that are used by
		 * mac_veriexec_check_fingerprint().
		 */
		bzero(&img, sizeof(img));
		img.proc = td->td_proc;
		img.vp = fp->f_vnode;
		img.attr = &va;

		/*
		 * Get vnode attributes
		 * (need to obtain a lock on the vnode first)
		 */
		vn_lock(img.vp, LK_EXCLUSIVE | LK_RETRY);
		error = VOP_GETATTR(fp->f_vnode, &va,  td->td_ucred);
		if (error)
			goto check_done;
		       
		MAC_VERIEXEC_DBG(2, "mac_veriexec_fingerprint_check_image: "
		    "va_mode=%o, check_files=%d\n", va.va_mode,
		    ((va.va_mode & (S_IXUSR|S_IXGRP|S_IXOTH)) == 0));
		error = mac_veriexec_fingerprint_check_image(&img,
		    ((va.va_mode & (S_IXUSR|S_IXGRP|S_IXOTH)) == 0), td);
check_done:
		/* Release the lock we obtained earlier */
		VOP_UNLOCK(img.vp, 0);
cleanup_file:
		fdrop(fp, td);
		break;
	case MAC_VERIEXEC_CHECK_PATH_SYSCALL:
		/* Look up the path to get the vnode */
		NDINIT(&nd, LOOKUP,
		    FOLLOW | LOCKLEAF | LOCKSHARED | AUDITVNODE1,
		    UIO_USERSPACE, arg, td);
		error = namei(&nd);
		if (error != 0)
			break;
		NDFREE(&nd, NDF_ONLY_PNBUF);

		/* Check the fingerprint status of the vnode */
		error = mac_veriexec_check_vp(td->td_ucred, nd.ni_vp, VVERIFY);
		vput(nd.ni_vp);
		break;
	default:
		error = EOPNOTSUPP;
	}
	return (error);
}