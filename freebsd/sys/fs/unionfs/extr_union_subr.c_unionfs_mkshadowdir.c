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
typedef  int /*<<< orphan*/  uid_t ;
struct vnode {int dummy; } ;
struct vattr {int /*<<< orphan*/  va_type; } ;
struct unionfs_node {struct vnode* un_lowervp; struct vnode* un_uppervp; } ;
struct unionfs_mount {int dummy; } ;
struct uidinfo {int dummy; } ;
struct ucred {int /*<<< orphan*/  cr_ruidinfo; } ;
struct thread {int dummy; } ;
struct mount {int dummy; } ;
struct componentname {int cn_flags; struct ucred* cn_cred; int /*<<< orphan*/  cn_pnbuf; int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;
typedef  int /*<<< orphan*/  cn ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE ; 
 int EEXIST ; 
 int HASBUF ; 
 struct vnode* NULLVP ; 
 int PCATCH ; 
 int /*<<< orphan*/  VNON ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 int VOP_MKDIR (struct vnode*,struct vnode**,struct componentname*,struct vattr*) ; 
 int /*<<< orphan*/  VOP_SETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 int V_WAIT ; 
 int /*<<< orphan*/  change_euid (struct ucred*,struct uidinfo*) ; 
 int /*<<< orphan*/  change_ruid (struct ucred*,struct uidinfo*) ; 
 int /*<<< orphan*/  change_svuid (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chgproccnt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ucred* crdup (struct ucred*) ; 
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 int /*<<< orphan*/  memset (struct componentname*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  namei_zone ; 
 struct uidinfo* uifind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uifree (struct uidinfo*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unionfs_create_uppervattr_core (struct unionfs_mount*,struct vattr*,struct vattr*,struct thread*) ; 
 int /*<<< orphan*/  unionfs_node_update (struct unionfs_node*,struct vnode*,struct thread*) ; 
 int unionfs_relookup (struct vnode*,struct vnode**,struct componentname*,struct componentname*,struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int vn_start_write (struct vnode*,struct mount**,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
unionfs_mkshadowdir(struct unionfs_mount *ump, struct vnode *udvp,
		    struct unionfs_node *unp, struct componentname *cnp,
		    struct thread *td)
{
	int		error;
	struct vnode   *lvp;
	struct vnode   *uvp;
	struct vattr	va;
	struct vattr	lva;
	struct componentname cn;
	struct mount   *mp;
	struct ucred   *cred;
	struct ucred   *credbk;
	struct uidinfo *rootinfo;

	if (unp->un_uppervp != NULLVP)
		return (EEXIST);

	lvp = unp->un_lowervp;
	uvp = NULLVP;
	credbk = cnp->cn_cred;

	/* Authority change to root */
	rootinfo = uifind((uid_t)0);
	cred = crdup(cnp->cn_cred);
	/*
	 * The calls to chgproccnt() are needed to compensate for change_ruid()
	 * calling chgproccnt().
	 */
	chgproccnt(cred->cr_ruidinfo, 1, 0);
	change_euid(cred, rootinfo);
	change_ruid(cred, rootinfo);
	change_svuid(cred, (uid_t)0);
	uifree(rootinfo);
	cnp->cn_cred = cred;

	memset(&cn, 0, sizeof(cn));

	if ((error = VOP_GETATTR(lvp, &lva, cnp->cn_cred)))
		goto unionfs_mkshadowdir_abort;

	if ((error = unionfs_relookup(udvp, &uvp, cnp, &cn, td, cnp->cn_nameptr, cnp->cn_namelen, CREATE)))
		goto unionfs_mkshadowdir_abort;
	if (uvp != NULLVP) {
		if (udvp == uvp)
			vrele(uvp);
		else
			vput(uvp);

		error = EEXIST;
		goto unionfs_mkshadowdir_free_out;
	}

	if ((error = vn_start_write(udvp, &mp, V_WAIT | PCATCH)))
		goto unionfs_mkshadowdir_free_out;
	unionfs_create_uppervattr_core(ump, &lva, &va, td);

	error = VOP_MKDIR(udvp, &uvp, &cn, &va);

	if (!error) {
		unionfs_node_update(unp, uvp, td);

		/*
		 * XXX The bug which cannot set uid/gid was corrected.
		 * Ignore errors.
		 */
		va.va_type = VNON;
		VOP_SETATTR(uvp, &va, cn.cn_cred);
	}
	vn_finished_write(mp);

unionfs_mkshadowdir_free_out:
	if (cn.cn_flags & HASBUF) {
		uma_zfree(namei_zone, cn.cn_pnbuf);
		cn.cn_flags &= ~HASBUF;
	}

unionfs_mkshadowdir_abort:
	cnp->cn_cred = credbk;
	chgproccnt(cred->cr_ruidinfo, -1, 0);
	crfree(cred);

	return (error);
}