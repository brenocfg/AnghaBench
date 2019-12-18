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
struct rwlock {int dummy; } ;
struct namecache {int nc_flag; struct vnode* nc_vp; struct vnode* nc_dvp; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int NCF_NEGATIVE ; 
 struct rwlock* NCP2BUCKETLOCK (struct namecache*) ; 
 struct mtx* VP2VNODELOCK (struct vnode*) ; 
 int /*<<< orphan*/  cache_assert_vnode_locked (struct vnode*) ; 
 int /*<<< orphan*/  cache_sort_vnodes (struct mtx**,struct mtx**) ; 
 int /*<<< orphan*/  cache_zap_locked (struct namecache*,int) ; 
 int /*<<< orphan*/  cache_zap_negative_locked_vnode_kl (struct namecache*,struct vnode*) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_trylock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  rw_wlock (struct rwlock*) ; 
 int /*<<< orphan*/  rw_wunlock (struct rwlock*) ; 

__attribute__((used)) static bool
cache_zap_locked_vnode_kl2(struct namecache *ncp, struct vnode *vp,
    struct mtx **vlpp)
{
	struct mtx *pvlp, *vlp1, *vlp2, *to_unlock;
	struct rwlock *blp;

	MPASS(vp == ncp->nc_dvp || vp == ncp->nc_vp);
	cache_assert_vnode_locked(vp);

	if (ncp->nc_flag & NCF_NEGATIVE) {
		if (*vlpp != NULL) {
			mtx_unlock(*vlpp);
			*vlpp = NULL;
		}
		cache_zap_negative_locked_vnode_kl(ncp, vp);
		return (true);
	}

	pvlp = VP2VNODELOCK(vp);
	blp = NCP2BUCKETLOCK(ncp);
	vlp1 = VP2VNODELOCK(ncp->nc_dvp);
	vlp2 = VP2VNODELOCK(ncp->nc_vp);

	if (*vlpp == vlp1 || *vlpp == vlp2) {
		to_unlock = *vlpp;
		*vlpp = NULL;
	} else {
		if (*vlpp != NULL) {
			mtx_unlock(*vlpp);
			*vlpp = NULL;
		}
		cache_sort_vnodes(&vlp1, &vlp2);
		if (vlp1 == pvlp) {
			mtx_lock(vlp2);
			to_unlock = vlp2;
		} else {
			if (!mtx_trylock(vlp1))
				goto out_relock;
			to_unlock = vlp1;
		}
	}
	rw_wlock(blp);
	cache_zap_locked(ncp, false);
	rw_wunlock(blp);
	if (to_unlock != NULL)
		mtx_unlock(to_unlock);
	return (true);

out_relock:
	mtx_unlock(vlp2);
	mtx_lock(vlp1);
	mtx_lock(vlp2);
	MPASS(*vlpp == NULL);
	*vlpp = vlp1;
	return (false);
}