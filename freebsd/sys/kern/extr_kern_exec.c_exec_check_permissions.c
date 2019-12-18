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
struct vnode {TYPE_1__* v_mount; } ;
struct vattr {int va_mode; scalar_t__ va_type; scalar_t__ va_size; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct image_params {int textset; int opened; struct vnode* vp; struct vattr* attr; } ;
struct TYPE_2__ {int mnt_flag; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOEXEC ; 
 int /*<<< orphan*/  FREAD ; 
 int MNT_NOEXEC ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  VEXEC ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 int VOP_OPEN (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,int /*<<< orphan*/ *) ; 
 int VOP_SET_TEXT (struct vnode*) ; 
 scalar_t__ VREG ; 
 struct thread* curthread ; 
 int mac_vnode_check_exec (int /*<<< orphan*/ ,struct vnode*,struct image_params*) ; 

int
exec_check_permissions(struct image_params *imgp)
{
	struct vnode *vp = imgp->vp;
	struct vattr *attr = imgp->attr;
	struct thread *td;
	int error;

	td = curthread;

	/* Get file attributes */
	error = VOP_GETATTR(vp, attr, td->td_ucred);
	if (error)
		return (error);

#ifdef MAC
	error = mac_vnode_check_exec(td->td_ucred, imgp->vp, imgp);
	if (error)
		return (error);
#endif

	/*
	 * 1) Check if file execution is disabled for the filesystem that
	 *    this file resides on.
	 * 2) Ensure that at least one execute bit is on. Otherwise, a
	 *    privileged user will always succeed, and we don't want this
	 *    to happen unless the file really is executable.
	 * 3) Ensure that the file is a regular file.
	 */
	if ((vp->v_mount->mnt_flag & MNT_NOEXEC) ||
	    (attr->va_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) == 0 ||
	    (attr->va_type != VREG))
		return (EACCES);

	/*
	 * Zero length files can't be exec'd
	 */
	if (attr->va_size == 0)
		return (ENOEXEC);

	/*
	 *  Check for execute permission to file based on current credentials.
	 */
	error = VOP_ACCESS(vp, VEXEC, td->td_ucred, td);
	if (error)
		return (error);

	/*
	 * Check number of open-for-writes on the file and deny execution
	 * if there are any.
	 *
	 * Add a text reference now so no one can write to the
	 * executable while we're activating it.
	 *
	 * Remember if this was set before and unset it in case this is not
	 * actually an executable image.
	 */
	error = VOP_SET_TEXT(vp);
	if (error != 0)
		return (error);
	imgp->textset = true;

	/*
	 * Call filesystem specific open routine (which does nothing in the
	 * general case).
	 */
	error = VOP_OPEN(vp, FREAD, td->td_ucred, td, NULL);
	if (error == 0)
		imgp->opened = 1;
	return (error);
}