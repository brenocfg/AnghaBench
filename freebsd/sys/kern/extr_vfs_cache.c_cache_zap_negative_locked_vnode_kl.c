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
struct namecache {int nc_flag; struct vnode* nc_dvp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int NCF_NEGATIVE ; 
 struct rwlock* NCP2BUCKETLOCK (struct namecache*) ; 
 int /*<<< orphan*/  cache_assert_vnode_locked (struct vnode*) ; 
 int /*<<< orphan*/  cache_zap_locked (struct namecache*,int) ; 
 int /*<<< orphan*/  rw_wlock (struct rwlock*) ; 
 int /*<<< orphan*/  rw_wunlock (struct rwlock*) ; 

__attribute__((used)) static void
cache_zap_negative_locked_vnode_kl(struct namecache *ncp, struct vnode *vp)
{
	struct rwlock *blp;

	MPASS(ncp->nc_dvp == vp);
	MPASS(ncp->nc_flag & NCF_NEGATIVE);
	cache_assert_vnode_locked(vp);

	blp = NCP2BUCKETLOCK(ncp);
	rw_wlock(blp);
	cache_zap_locked(ncp, false);
	rw_wunlock(blp);
}