#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct namecache {int nc_flag; TYPE_1__* nc_dvp; int /*<<< orphan*/  nc_name; TYPE_1__* nc_vp; } ;
struct TYPE_6__ {int /*<<< orphan*/  v_cache_src; struct namecache* v_cache_dd; int /*<<< orphan*/  v_cache_dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,struct namecache*,TYPE_1__*) ; 
 int /*<<< orphan*/  KTR_VFS ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct namecache*,int /*<<< orphan*/ ) ; 
 int NCF_DVDROP ; 
 int NCF_ISDOTDOT ; 
 int NCF_NEGATIVE ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  SDT_PROBE2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDT_PROBE3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct namecache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_subtract_rel_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cache_assert_bucket_locked (struct namecache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_assert_vnode_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  cache_negative_remove (struct namecache*,int) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  namecache ; 
 int /*<<< orphan*/  nc_dst ; 
 int /*<<< orphan*/  nc_hash ; 
 int /*<<< orphan*/  nc_src ; 
 int /*<<< orphan*/  numcache ; 
 int /*<<< orphan*/  numcachehv ; 
 int /*<<< orphan*/  vfs ; 
 int /*<<< orphan*/  zap ; 
 int /*<<< orphan*/  zap_negative ; 

__attribute__((used)) static void
cache_zap_locked(struct namecache *ncp, bool neg_locked)
{

	if (!(ncp->nc_flag & NCF_NEGATIVE))
		cache_assert_vnode_locked(ncp->nc_vp);
	cache_assert_vnode_locked(ncp->nc_dvp);
	cache_assert_bucket_locked(ncp, RA_WLOCKED);

	CTR2(KTR_VFS, "cache_zap(%p) vp %p", ncp,
	    (ncp->nc_flag & NCF_NEGATIVE) ? NULL : ncp->nc_vp);
	LIST_REMOVE(ncp, nc_hash);
	if (!(ncp->nc_flag & NCF_NEGATIVE)) {
		SDT_PROBE3(vfs, namecache, zap, done, ncp->nc_dvp,
		    ncp->nc_name, ncp->nc_vp);
		TAILQ_REMOVE(&ncp->nc_vp->v_cache_dst, ncp, nc_dst);
		if (ncp == ncp->nc_vp->v_cache_dd)
			ncp->nc_vp->v_cache_dd = NULL;
	} else {
		SDT_PROBE2(vfs, namecache, zap_negative, done, ncp->nc_dvp,
		    ncp->nc_name);
		cache_negative_remove(ncp, neg_locked);
	}
	if (ncp->nc_flag & NCF_ISDOTDOT) {
		if (ncp == ncp->nc_dvp->v_cache_dd)
			ncp->nc_dvp->v_cache_dd = NULL;
	} else {
		LIST_REMOVE(ncp, nc_src);
		if (LIST_EMPTY(&ncp->nc_dvp->v_cache_src)) {
			ncp->nc_flag |= NCF_DVDROP;
			atomic_subtract_rel_long(&numcachehv, 1);
		}
	}
	atomic_subtract_rel_long(&numcache, 1);
}