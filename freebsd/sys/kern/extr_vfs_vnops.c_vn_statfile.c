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
struct thread {int dummy; } ;
struct stat {int dummy; } ;
struct file {int /*<<< orphan*/  f_cred; struct vnode* f_vnode; } ;

/* Variables and functions */
 int LK_RETRY ; 
 int LK_SHARED ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int vn_stat (struct vnode*,struct stat*,struct ucred*,int /*<<< orphan*/ ,struct thread*) ; 

__attribute__((used)) static int
vn_statfile(struct file *fp, struct stat *sb, struct ucred *active_cred,
    struct thread *td)
{
	struct vnode *vp = fp->f_vnode;
	int error;

	vn_lock(vp, LK_SHARED | LK_RETRY);
	error = vn_stat(vp, sb, active_cred, fp->f_cred, td);
	VOP_UNLOCK(vp, 0);

	return (error);
}