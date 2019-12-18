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
 int /*<<< orphan*/  MPASS (int) ; 
 int NCF_HOTNEGATIVE ; 
 int NCF_NEGATIVE ; 
 struct neglist* NCP2NEGLIST (struct namecache*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct namecache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct namecache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nc_dst ; 
 TYPE_1__ ncneg_hot ; 
 int /*<<< orphan*/  numhotneg ; 

__attribute__((used)) static void
cache_negative_hit(struct namecache *ncp)
{
	struct neglist *neglist;

	MPASS(ncp->nc_flag & NCF_NEGATIVE);
	if (ncp->nc_flag & NCF_HOTNEGATIVE)
		return;
	neglist = NCP2NEGLIST(ncp);
	mtx_lock(&ncneg_hot.nl_lock);
	mtx_lock(&neglist->nl_lock);
	if (!(ncp->nc_flag & NCF_HOTNEGATIVE)) {
		numhotneg++;
		TAILQ_REMOVE(&neglist->nl_list, ncp, nc_dst);
		TAILQ_INSERT_TAIL(&ncneg_hot.nl_list, ncp, nc_dst);
		ncp->nc_flag |= NCF_HOTNEGATIVE;
	}
	mtx_unlock(&neglist->nl_lock);
	mtx_unlock(&ncneg_hot.nl_lock);
}