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
struct neglist {int /*<<< orphan*/  nl_lock; int /*<<< orphan*/  nl_list; } ;
struct namecache {int nc_flag; } ;
struct TYPE_2__ {int /*<<< orphan*/  nl_lock; int /*<<< orphan*/  nl_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int NCF_HOTNEGATIVE ; 
 int NCF_NEGATIVE ; 
 struct neglist* NCP2NEGLIST (struct namecache*) ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct namecache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_subtract_rel_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cache_assert_bucket_locked (struct namecache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nc_dst ; 
 TYPE_1__ ncneg_hot ; 
 int /*<<< orphan*/  numhotneg ; 
 int /*<<< orphan*/  numneg ; 

__attribute__((used)) static void
cache_negative_remove(struct namecache *ncp, bool neg_locked)
{
	struct neglist *neglist;
	bool hot_locked = false;
	bool list_locked = false;

	MPASS(ncp->nc_flag & NCF_NEGATIVE);
	cache_assert_bucket_locked(ncp, RA_WLOCKED);
	neglist = NCP2NEGLIST(ncp);
	if (!neg_locked) {
		if (ncp->nc_flag & NCF_HOTNEGATIVE) {
			hot_locked = true;
			mtx_lock(&ncneg_hot.nl_lock);
			if (!(ncp->nc_flag & NCF_HOTNEGATIVE)) {
				list_locked = true;
				mtx_lock(&neglist->nl_lock);
			}
		} else {
			list_locked = true;
			mtx_lock(&neglist->nl_lock);
		}
	}
	if (ncp->nc_flag & NCF_HOTNEGATIVE) {
		mtx_assert(&ncneg_hot.nl_lock, MA_OWNED);
		TAILQ_REMOVE(&ncneg_hot.nl_list, ncp, nc_dst);
		numhotneg--;
	} else {
		mtx_assert(&neglist->nl_lock, MA_OWNED);
		TAILQ_REMOVE(&neglist->nl_list, ncp, nc_dst);
	}
	if (list_locked)
		mtx_unlock(&neglist->nl_lock);
	if (hot_locked)
		mtx_unlock(&ncneg_hot.nl_lock);
	atomic_subtract_rel_long(&numneg, 1);
}