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
struct componentname {int cn_flags; int /*<<< orphan*/  cn_pnbuf; int /*<<< orphan*/  cn_nameptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE ; 
 int EEXIST ; 
 int HASBUF ; 
 struct vnode* NULLVP ; 
 struct vnode* UNIONFSVPTOUPPERVP (struct vnode*) ; 
 int /*<<< orphan*/  namei_zone ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int unionfs_relookup (struct vnode*,struct vnode**,struct componentname*,struct componentname*,struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
unionfs_relookup_for_create(struct vnode *dvp, struct componentname *cnp,
			    struct thread *td)
{
	int	error;
	struct vnode *udvp;
	struct vnode *vp;
	struct componentname cn;

	udvp = UNIONFSVPTOUPPERVP(dvp);
	vp = NULLVP;

	error = unionfs_relookup(udvp, &vp, cnp, &cn, td, cnp->cn_nameptr,
	    strlen(cnp->cn_nameptr), CREATE);
	if (error)
		return (error);

	if (vp != NULLVP) {
		if (udvp == vp)
			vrele(vp);
		else
			vput(vp);

		error = EEXIST;
	}

	if (cn.cn_flags & HASBUF) {
		uma_zfree(namei_zone, cn.cn_pnbuf);
		cn.cn_flags &= ~HASBUF;
	}

	if (!error) {
		cn.cn_flags |= (cnp->cn_flags & HASBUF);
		cnp->cn_flags = cn.cn_flags;
	}

	return (error);
}