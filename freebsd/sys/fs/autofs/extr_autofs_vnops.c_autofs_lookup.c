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
struct vop_lookup_args {struct componentname* a_cnp; struct vnode** a_vpp; struct vnode* a_dvp; } ;
struct vnode {struct autofs_node* v_data; struct mount* v_mount; } ;
struct mount {int dummy; } ;
struct componentname {int cn_flags; int cn_namelen; char* cn_nameptr; scalar_t__ cn_nameiop; int /*<<< orphan*/  cn_lkflags; int /*<<< orphan*/  cn_thread; } ;
struct autofs_node {int /*<<< orphan*/ * an_parent; } ;
struct autofs_mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_SLOCK (struct autofs_mount*) ; 
 int /*<<< orphan*/  AUTOFS_SUNLOCK (struct autofs_mount*) ; 
 int /*<<< orphan*/  AUTOFS_WARN (char*,int) ; 
 scalar_t__ CREATE ; 
 int EJUSTRETURN ; 
 int ENOENT ; 
 int ERELOOKUP ; 
 int ISDOTDOT ; 
 int ISLASTCN ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct autofs_mount* VFSTOAUTOFS (struct mount*) ; 
 int autofs_cached (struct autofs_node*,char*,int) ; 
 int autofs_ignore_thread (int /*<<< orphan*/ ) ; 
 int autofs_node_find (struct autofs_node*,char*,int,struct autofs_node**) ; 
 int autofs_node_vn (struct autofs_node*,struct mount*,int /*<<< orphan*/ ,struct vnode**) ; 
 int autofs_trigger_vn (struct vnode*,char*,int,struct vnode**) ; 
 int /*<<< orphan*/  autofs_vget_callback ; 
 int vn_vget_ino_gen (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vnode**) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vref (struct vnode*) ; 

__attribute__((used)) static int
autofs_lookup(struct vop_lookup_args *ap)
{
	struct vnode *dvp, *newvp, **vpp;
	struct mount *mp;
	struct autofs_mount *amp;
	struct autofs_node *anp, *child;
	struct componentname *cnp;
	int error;

	dvp = ap->a_dvp;
	vpp = ap->a_vpp;
	mp = dvp->v_mount;
	amp = VFSTOAUTOFS(mp);
	anp = dvp->v_data;
	cnp = ap->a_cnp;

	if (cnp->cn_flags & ISDOTDOT) {
		KASSERT(anp->an_parent != NULL, ("NULL parent"));
		/*
		 * Note that in this case, dvp is the child vnode, and we
		 * are looking up the parent vnode - exactly reverse from
		 * normal operation.  Unlocking dvp requires some rather
		 * tricky unlock/relock dance to prevent mp from being freed;
		 * use vn_vget_ino_gen() which takes care of all that.
		 */
		error = vn_vget_ino_gen(dvp, autofs_vget_callback,
		    anp->an_parent, cnp->cn_lkflags, vpp);
		if (error != 0) {
			AUTOFS_WARN("vn_vget_ino_gen() failed with error %d",
			    error);
			return (error);
		}
		return (error);
	}

	if (cnp->cn_namelen == 1 && cnp->cn_nameptr[0] == '.') {
		vref(dvp);
		*vpp = dvp;

		return (0);
	}

	if (autofs_cached(anp, cnp->cn_nameptr, cnp->cn_namelen) == false &&
	    autofs_ignore_thread(cnp->cn_thread) == false) {
		error = autofs_trigger_vn(dvp,
		    cnp->cn_nameptr, cnp->cn_namelen, &newvp);
		if (error != 0)
			return (error);

		if (newvp != NULL) {
			/*
			 * The target filesystem got automounted.
			 * Let the lookup(9) go around with the same
			 * path component.
			 */
			vput(newvp);
			return (ERELOOKUP);
		}
	}

	AUTOFS_SLOCK(amp);
	error = autofs_node_find(anp, cnp->cn_nameptr, cnp->cn_namelen, &child);
	if (error != 0) {
		if ((cnp->cn_flags & ISLASTCN) && cnp->cn_nameiop == CREATE) {
			AUTOFS_SUNLOCK(amp);
			return (EJUSTRETURN);
		}

		AUTOFS_SUNLOCK(amp);
		return (ENOENT);
	}

	/*
	 * XXX: Dropping the node here is ok, because we never remove nodes.
	 */
	AUTOFS_SUNLOCK(amp);

	error = autofs_node_vn(child, mp, cnp->cn_lkflags, vpp);
	if (error != 0) {
		if ((cnp->cn_flags & ISLASTCN) && cnp->cn_nameiop == CREATE)
			return (EJUSTRETURN);

		return (error);
	}

	return (0);
}