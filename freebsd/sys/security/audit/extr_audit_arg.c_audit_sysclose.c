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
struct vnode {int dummy; } ;
struct thread {int dummy; } ;
struct kaudit_record {int dummy; } ;
struct file {struct vnode* f_vnode; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_arg_fd (int) ; 
 int /*<<< orphan*/  audit_arg_vnode1 (struct vnode*) ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *) ; 
 struct kaudit_record* currecord () ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 scalar_t__ getvnode (struct thread*,int,int /*<<< orphan*/ ,struct file**) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

void
audit_sysclose(struct thread *td, int fd)
{
	cap_rights_t rights;
	struct kaudit_record *ar;
	struct vnode *vp;
	struct file *fp;

	KASSERT(td != NULL, ("audit_sysclose: td == NULL"));

	ar = currecord();
	if (ar == NULL)
		return;

	audit_arg_fd(fd);

	if (getvnode(td, fd, cap_rights_init(&rights), &fp) != 0)
		return;

	vp = fp->f_vnode;
	vn_lock(vp, LK_SHARED | LK_RETRY);
	audit_arg_vnode1(vp);
	VOP_UNLOCK(vp, 0);
	fdrop(fp, td);
}