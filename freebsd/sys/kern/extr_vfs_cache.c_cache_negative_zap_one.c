#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rwlock {int dummy; } ;
struct mtx {int dummy; } ;
struct neglist {struct mtx nl_lock; int /*<<< orphan*/  nl_list; } ;
struct namecache {int nc_flag; int /*<<< orphan*/  nc_name; int /*<<< orphan*/  nc_dvp; } ;
struct TYPE_2__ {struct mtx nl_lock; int /*<<< orphan*/  nl_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int NCF_HOTNEGATIVE ; 
 int NCF_NEGATIVE ; 
 struct rwlock* NCP2BUCKETLOCK (struct namecache*) ; 
 struct neglist* NCP2NEGLIST (struct namecache*) ; 
 int /*<<< orphan*/  SDT_PROBE2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct namecache* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct namecache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct namecache*,int /*<<< orphan*/ ) ; 
 struct mtx* VP2VNODELOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_free (struct namecache*) ; 
 int /*<<< orphan*/  cache_negative_shrink_select (scalar_t__,struct namecache**,struct neglist**) ; 
 int /*<<< orphan*/  cache_zap_locked (struct namecache*,int) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/ * mtx_owner (struct mtx*) ; 
 int /*<<< orphan*/  mtx_trylock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  namecache ; 
 int /*<<< orphan*/  nc_dst ; 
 TYPE_1__ ncneg_hot ; 
 struct mtx ncneg_shrink_lock ; 
 int /*<<< orphan*/  numhotneg ; 
 int /*<<< orphan*/  numneg_evicted ; 
 scalar_t__ numneglists ; 
 int /*<<< orphan*/  rw_wlock (struct rwlock*) ; 
 int /*<<< orphan*/  rw_wunlock (struct rwlock*) ; 
 scalar_t__ shrink_list_turn ; 
 int /*<<< orphan*/  shrink_negative ; 
 int /*<<< orphan*/  shrinking_skipped ; 
 int /*<<< orphan*/  vfs ; 

__attribute__((used)) static void
cache_negative_zap_one(void)
{
	struct namecache *ncp, *ncp2;
	struct neglist *neglist;
	struct mtx *dvlp;
	struct rwlock *blp;

	if (mtx_owner(&ncneg_shrink_lock) != NULL ||
	    !mtx_trylock(&ncneg_shrink_lock)) {
		counter_u64_add(shrinking_skipped, 1);
		return;
	}

	mtx_lock(&ncneg_hot.nl_lock);
	ncp = TAILQ_FIRST(&ncneg_hot.nl_list);
	if (ncp != NULL) {
		neglist = NCP2NEGLIST(ncp);
		mtx_lock(&neglist->nl_lock);
		TAILQ_REMOVE(&ncneg_hot.nl_list, ncp, nc_dst);
		TAILQ_INSERT_TAIL(&neglist->nl_list, ncp, nc_dst);
		ncp->nc_flag &= ~NCF_HOTNEGATIVE;
		numhotneg--;
		mtx_unlock(&neglist->nl_lock);
	}
	mtx_unlock(&ncneg_hot.nl_lock);

	cache_negative_shrink_select(shrink_list_turn, &ncp, &neglist);
	shrink_list_turn++;
	if (shrink_list_turn == numneglists)
		shrink_list_turn = 0;
	if (ncp == NULL && shrink_list_turn == 0)
		cache_negative_shrink_select(shrink_list_turn, &ncp, &neglist);
	mtx_unlock(&ncneg_shrink_lock);
	if (ncp == NULL)
		return;

	MPASS(ncp->nc_flag & NCF_NEGATIVE);
	dvlp = VP2VNODELOCK(ncp->nc_dvp);
	blp = NCP2BUCKETLOCK(ncp);
	mtx_unlock(&neglist->nl_lock);
	mtx_lock(dvlp);
	rw_wlock(blp);
	mtx_lock(&neglist->nl_lock);
	ncp2 = TAILQ_FIRST(&neglist->nl_list);
	if (ncp != ncp2 || dvlp != VP2VNODELOCK(ncp2->nc_dvp) ||
	    blp != NCP2BUCKETLOCK(ncp2) || !(ncp2->nc_flag & NCF_NEGATIVE)) {
		ncp = NULL;
	} else {
		SDT_PROBE2(vfs, namecache, shrink_negative, done, ncp->nc_dvp,
		    ncp->nc_name);

		cache_zap_locked(ncp, true);
		counter_u64_add(numneg_evicted, 1);
	}
	mtx_unlock(&neglist->nl_lock);
	rw_wunlock(blp);
	mtx_unlock(dvlp);
	cache_free(ncp);
}