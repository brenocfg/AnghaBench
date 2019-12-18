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
typedef  scalar_t__ u_long ;
struct vop_bmap_args {int* a_bnp; int* a_runp; int* a_runb; scalar_t__ a_bn; int /*<<< orphan*/ ** a_bop; struct vnode* a_vp; } ;
struct vnode {struct mount* v_mount; } ;
struct msdosfsmount {scalar_t__ pm_maxcluster; TYPE_1__* pm_devvp; } ;
struct TYPE_4__ {int f_iosize; } ;
struct mount {int mnt_iosize_max; TYPE_2__ mnt_stat; } ;
struct fatcache {int dummy; } ;
struct denode {struct fatcache* de_fc; struct msdosfsmount* de_pmp; } ;
typedef  int daddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  v_bufobj; } ;

/* Variables and functions */
 int EFBIG ; 
 size_t FC_LASTMAP ; 
 struct denode* VTODE (struct vnode*) ; 
 int de_cn2bn (struct msdosfsmount*,int) ; 
 int pcbmap (struct denode*,scalar_t__,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ulmin (int,scalar_t__) ; 

__attribute__((used)) static int
msdosfs_bmap(struct vop_bmap_args *ap)
{
	struct fatcache savefc;
	struct denode *dep;
	struct mount *mp;
	struct msdosfsmount *pmp;
	struct vnode *vp;
	daddr_t runbn;
	u_long cn;
	int bnpercn, error, maxio, maxrun, run;

	vp = ap->a_vp;
	dep = VTODE(vp);
	pmp = dep->de_pmp;
	if (ap->a_bop != NULL)
		*ap->a_bop = &pmp->pm_devvp->v_bufobj;
	if (ap->a_bnp == NULL)
		return (0);
	if (ap->a_runp != NULL)
		*ap->a_runp = 0;
	if (ap->a_runb != NULL)
		*ap->a_runb = 0;
	cn = ap->a_bn;
	if (cn != ap->a_bn)
		return (EFBIG);
	error = pcbmap(dep, cn, ap->a_bnp, NULL, NULL);
	if (error != 0 || (ap->a_runp == NULL && ap->a_runb == NULL))
		return (error);

	/*
	 * Prepare to back out updates of the fatchain cache after the one
	 * for the first block done by pcbmap() above.  Without the backout,
	 * then whenever the caller doesn't do i/o to all of the blocks that
	 * we find, the single useful cache entry would be too far in advance
	 * of the actual i/o to work for the next sequential i/o.  Then the
	 * FAT would be searched from the beginning.  With the backout, the
	 * FAT is searched starting at most a few blocks early.  This wastes
	 * much less time.  Time is also wasted finding more blocks than the
	 * caller will do i/o to.  This is necessary because the runlength
	 * parameters are output-only.
	 */
	savefc = dep->de_fc[FC_LASTMAP];

	mp = vp->v_mount;
	maxio = mp->mnt_iosize_max / mp->mnt_stat.f_iosize;
	bnpercn = de_cn2bn(pmp, 1);
	if (ap->a_runp != NULL) {
		maxrun = ulmin(maxio - 1, pmp->pm_maxcluster - cn);
		for (run = 1; run <= maxrun; run++) {
			if (pcbmap(dep, cn + run, &runbn, NULL, NULL) != 0 ||
			    runbn != *ap->a_bnp + run * bnpercn)
				break;
		}
		*ap->a_runp = run - 1;
	}
	if (ap->a_runb != NULL) {
		maxrun = ulmin(maxio - 1, cn);
		for (run = 1; run < maxrun; run++) {
			if (pcbmap(dep, cn - run, &runbn, NULL, NULL) != 0 ||
			    runbn != *ap->a_bnp - run * bnpercn)
				break;
		}
		*ap->a_runb = run - 1;
	}
	dep->de_fc[FC_LASTMAP] = savefc;
	return (0);
}