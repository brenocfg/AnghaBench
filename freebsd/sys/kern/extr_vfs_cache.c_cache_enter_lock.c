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
typedef  int /*<<< orphan*/  uint32_t ;
struct vnode {scalar_t__ v_type; struct namecache* v_cache_dd; } ;
struct rwlock {int dummy; } ;
struct namecache {int nc_flag; int /*<<< orphan*/  nc_vp; struct vnode* nc_dvp; } ;
struct celockstate {int /*<<< orphan*/ ** vlp; } ;

/* Variables and functions */
 struct rwlock* HASH2BUCKETLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int NCF_ISDOTDOT ; 
 int NCF_NEGATIVE ; 
 struct rwlock* NCP2BUCKETLOCK (struct namecache*) ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/ * VP2VNODELOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_lock_buckets_cel (struct celockstate*,struct rwlock*,struct rwlock*) ; 
 int /*<<< orphan*/  cache_lock_vnodes_cel (struct celockstate*,struct vnode*,struct vnode*) ; 
 scalar_t__ cache_lock_vnodes_cel_3 (struct celockstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_unlock_vnodes_cel (struct celockstate*) ; 

__attribute__((used)) static void
cache_enter_lock(struct celockstate *cel, struct vnode *dvp, struct vnode *vp,
    uint32_t hash)
{
	struct namecache *ncp;
	struct rwlock *blps[2];

	blps[0] = HASH2BUCKETLOCK(hash);
	for (;;) {
		blps[1] = NULL;
		cache_lock_vnodes_cel(cel, dvp, vp);
		if (vp == NULL || vp->v_type != VDIR)
			break;
		ncp = vp->v_cache_dd;
		if (ncp == NULL)
			break;
		if ((ncp->nc_flag & NCF_ISDOTDOT) == 0)
			break;
		MPASS(ncp->nc_dvp == vp);
		blps[1] = NCP2BUCKETLOCK(ncp);
		if (ncp->nc_flag & NCF_NEGATIVE)
			break;
		if (cache_lock_vnodes_cel_3(cel, ncp->nc_vp))
			break;
		/*
		 * All vnodes got re-locked. Re-validate the state and if
		 * nothing changed we are done. Otherwise restart.
		 */
		if (ncp == vp->v_cache_dd &&
		    (ncp->nc_flag & NCF_ISDOTDOT) != 0 &&
		    blps[1] == NCP2BUCKETLOCK(ncp) &&
		    VP2VNODELOCK(ncp->nc_vp) == cel->vlp[2])
			break;
		cache_unlock_vnodes_cel(cel);
		cel->vlp[0] = NULL;
		cel->vlp[1] = NULL;
		cel->vlp[2] = NULL;
	}
	cache_lock_buckets_cel(cel, blps[0], blps[1]);
}