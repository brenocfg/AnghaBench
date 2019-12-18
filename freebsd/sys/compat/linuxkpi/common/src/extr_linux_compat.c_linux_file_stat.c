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
struct ucred {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct stat {int dummy; } ;
struct linux_file {struct vnode* f_vnode; } ;
struct file {scalar_t__ f_data; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int vn_stat (struct vnode*,struct stat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 

__attribute__((used)) static int
linux_file_stat(struct file *fp, struct stat *sb, struct ucred *active_cred,
    struct thread *td)
{
	struct linux_file *filp;
	struct vnode *vp;
	int error;

	filp = (struct linux_file *)fp->f_data;
	if (filp->f_vnode == NULL)
		return (EOPNOTSUPP);

	vp = filp->f_vnode;

	vn_lock(vp, LK_SHARED | LK_RETRY);
	error = vn_stat(vp, sb, td->td_ucred, NOCRED, td);
	VOP_UNLOCK(vp, 0);

	return (error);
}