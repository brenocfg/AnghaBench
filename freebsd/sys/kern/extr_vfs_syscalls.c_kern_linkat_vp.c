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
struct vnode {scalar_t__ v_type; scalar_t__ v_mount; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nameidata {struct vnode* ni_dvp; int /*<<< orphan*/  ni_cnd; struct vnode* ni_vp; } ;
struct mount {int dummy; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int AUDITVNODE2 ; 
 int /*<<< orphan*/  CREATE ; 
 int EAGAIN ; 
 int EEXIST ; 
 int EPERM ; 
 int EXDEV ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int LOCKPARENT ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT_ATRIGHTS (struct nameidata*,int /*<<< orphan*/ ,int,int,char const*,int,int /*<<< orphan*/ *,struct thread*) ; 
 int NOCACHE ; 
 int PCATCH ; 
 int SAVENAME ; 
 scalar_t__ VDIR ; 
 int VOP_LINK (struct vnode*,struct vnode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int V_NOWAIT ; 
 int V_XSLEEP ; 
 int can_hardlink (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_linkat_target_rights ; 
 int mac_vnode_check_link (int /*<<< orphan*/ ,struct vnode*,struct vnode*,int /*<<< orphan*/ *) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int vn_lock (struct vnode*,int /*<<< orphan*/ ) ; 
 int vn_start_write (struct vnode*,struct mount**,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
kern_linkat_vp(struct thread *td, struct vnode *vp, int fd, const char *path,
    enum uio_seg segflag)
{
	struct nameidata nd;
	struct mount *mp;
	int error;

	if (vp->v_type == VDIR) {
		vrele(vp);
		return (EPERM);		/* POSIX */
	}
	NDINIT_ATRIGHTS(&nd, CREATE,
	    LOCKPARENT | SAVENAME | AUDITVNODE2 | NOCACHE, segflag, path, fd,
	    &cap_linkat_target_rights, td);
	if ((error = namei(&nd)) == 0) {
		if (nd.ni_vp != NULL) {
			NDFREE(&nd, NDF_ONLY_PNBUF);
			if (nd.ni_dvp == nd.ni_vp)
				vrele(nd.ni_dvp);
			else
				vput(nd.ni_dvp);
			vrele(nd.ni_vp);
			vrele(vp);
			return (EEXIST);
		} else if (nd.ni_dvp->v_mount != vp->v_mount) {
			/*
			 * Cross-device link.  No need to recheck
			 * vp->v_type, since it cannot change, except
			 * to VBAD.
			 */
			NDFREE(&nd, NDF_ONLY_PNBUF);
			vput(nd.ni_dvp);
			vrele(vp);
			return (EXDEV);
		} else if ((error = vn_lock(vp, LK_EXCLUSIVE)) == 0) {
			error = can_hardlink(vp, td->td_ucred);
#ifdef MAC
			if (error == 0)
				error = mac_vnode_check_link(td->td_ucred,
				    nd.ni_dvp, vp, &nd.ni_cnd);
#endif
			if (error != 0) {
				vput(vp);
				vput(nd.ni_dvp);
				NDFREE(&nd, NDF_ONLY_PNBUF);
				return (error);
			}
			error = vn_start_write(vp, &mp, V_NOWAIT);
			if (error != 0) {
				vput(vp);
				vput(nd.ni_dvp);
				NDFREE(&nd, NDF_ONLY_PNBUF);
				error = vn_start_write(NULL, &mp,
				    V_XSLEEP | PCATCH);
				if (error != 0)
					return (error);
				return (EAGAIN);
			}
			error = VOP_LINK(nd.ni_dvp, vp, &nd.ni_cnd);
			VOP_UNLOCK(vp, 0);
			vput(nd.ni_dvp);
			vn_finished_write(mp);
			NDFREE(&nd, NDF_ONLY_PNBUF);
		} else {
			vput(nd.ni_dvp);
			NDFREE(&nd, NDF_ONLY_PNBUF);
			vrele(vp);
			return (EAGAIN);
		}
	}
	vrele(vp);
	return (error);
}