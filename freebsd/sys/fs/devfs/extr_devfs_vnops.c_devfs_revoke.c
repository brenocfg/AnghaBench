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
typedef  size_t u_int ;
struct vop_revoke_args {int a_flags; struct vnode* a_vp; } ;
struct vnode {struct cdev* v_rdev; } ;
struct devfs_dirent {struct vnode* de_vnode; } ;
struct cdev_priv {scalar_t__ cdp_inuse; size_t cdp_maxdirent; int cdp_flags; int /*<<< orphan*/  cdp_c; struct devfs_dirent** cdp_dirents; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int CDP_ACTIVE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LK_EXCLUSIVE ; 
 int LK_INTERLOCK ; 
 int LK_RETRY ; 
 int REVOKEALL ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cdev_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VI_LOCK (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 struct cdev_priv* cdev2priv (struct cdev*) ; 
 int /*<<< orphan*/  cdevp_list ; 
 int /*<<< orphan*/  cdp_list ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  dev_lock () ; 
 int /*<<< orphan*/  dev_rel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_unlock () ; 
 int /*<<< orphan*/  devfs_de_interlock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 scalar_t__ vget (struct vnode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgone (struct vnode*) ; 
 int /*<<< orphan*/  vhold (struct vnode*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

__attribute__((used)) static int
devfs_revoke(struct vop_revoke_args *ap)
{
	struct vnode *vp = ap->a_vp, *vp2;
	struct cdev *dev;
	struct cdev_priv *cdp;
	struct devfs_dirent *de;
	u_int i;

	KASSERT((ap->a_flags & REVOKEALL) != 0, ("devfs_revoke !REVOKEALL"));

	dev = vp->v_rdev;
	cdp = cdev2priv(dev);
 
	dev_lock();
	cdp->cdp_inuse++;
	dev_unlock();

	vhold(vp);
	vgone(vp);
	vdrop(vp);

	VOP_UNLOCK(vp,0);
 loop:
	for (;;) {
		mtx_lock(&devfs_de_interlock);
		dev_lock();
		vp2 = NULL;
		for (i = 0; i <= cdp->cdp_maxdirent; i++) {
			de = cdp->cdp_dirents[i];
			if (de == NULL)
				continue;

			vp2 = de->de_vnode;
			if (vp2 != NULL) {
				dev_unlock();
				VI_LOCK(vp2);
				mtx_unlock(&devfs_de_interlock);
				if (vget(vp2, LK_EXCLUSIVE | LK_INTERLOCK,
				    curthread))
					goto loop;
				vhold(vp2);
				vgone(vp2);
				vdrop(vp2);
				vput(vp2);
				break;
			} 
		}
		if (vp2 != NULL) {
			continue;
		}
		dev_unlock();
		mtx_unlock(&devfs_de_interlock);
		break;
	}
	dev_lock();
	cdp->cdp_inuse--;
	if (!(cdp->cdp_flags & CDP_ACTIVE) && cdp->cdp_inuse == 0) {
		TAILQ_REMOVE(&cdevp_list, cdp, cdp_list);
		dev_unlock();
		dev_rel(&cdp->cdp_c);
	} else
		dev_unlock();

	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
	return (0);
}