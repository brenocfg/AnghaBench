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
struct neglist {int /*<<< orphan*/  nl_lock; int /*<<< orphan*/  nl_list; } ;
struct namecache {int nc_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int NCF_NEGATIVE ; 
 struct neglist* NCP2NEGLIST (struct namecache*) ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct namecache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_rel_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cache_assert_bucket_locked (struct namecache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nc_dst ; 
 int /*<<< orphan*/  numneg ; 

__attribute__((used)) static void
cache_negative_insert(struct namecache *ncp, bool neg_locked)
{
	struct neglist *neglist;

	MPASS(ncp->nc_flag & NCF_NEGATIVE);
	cache_assert_bucket_locked(ncp, RA_WLOCKED);
	neglist = NCP2NEGLIST(ncp);
	if (!neg_locked) {
		mtx_lock(&neglist->nl_lock);
	} else {
		mtx_assert(&neglist->nl_lock, MA_OWNED);
	}
	TAILQ_INSERT_TAIL(&neglist->nl_list, ncp, nc_dst);
	if (!neg_locked)
		mtx_unlock(&neglist->nl_lock);
	atomic_add_rel_long(&numneg, 1);
}