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
struct vop_access_args {TYPE_1__* a_td; int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_accmode; struct vnode* a_vp; } ;
struct vnode {scalar_t__ v_type; struct devfs_dirent* v_data; } ;
struct proc {int p_flag; TYPE_2__* p_session; } ;
struct devfs_dirent {scalar_t__ de_cdp; int /*<<< orphan*/  de_gid; int /*<<< orphan*/  de_uid; int /*<<< orphan*/  de_mode; struct devfs_dirent* de_dir; } ;
struct TYPE_4__ {scalar_t__ s_ttydp; } ;
struct TYPE_3__ {struct proc* td_proc; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_CONTROLT ; 
 scalar_t__ VDIR ; 
 int vaccess (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
devfs_access(struct vop_access_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct devfs_dirent *de;
	struct proc *p;
	int error;

	de = vp->v_data;
	if (vp->v_type == VDIR)
		de = de->de_dir;

	error = vaccess(vp->v_type, de->de_mode, de->de_uid, de->de_gid,
	    ap->a_accmode, ap->a_cred, NULL);
	if (error == 0)
		return (0);
	if (error != EACCES)
		return (error);
	p = ap->a_td->td_proc;
	/* We do, however, allow access to the controlling terminal */
	PROC_LOCK(p);
	if (!(p->p_flag & P_CONTROLT)) {
		PROC_UNLOCK(p);
		return (error);
	}
	if (p->p_session->s_ttydp == de->de_cdp)
		error = 0;
	PROC_UNLOCK(p);
	return (error);
}