#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* cfg; scalar_t__* modinfo; TYPE_1__* mesh; } ;
struct worker {TYPE_3__ env; } ;
struct val_neg_cache {int /*<<< orphan*/  lock; scalar_t__ num_neg_cache_nxdomain; scalar_t__ num_neg_cache_noerror; } ;
struct val_env {struct val_neg_cache* neg_cache; } ;
struct ub_server_stats {long long num_neg_cache_noerror; long long num_neg_cache_nxdomain; } ;
struct TYPE_5__ {int /*<<< orphan*/  stat_cumulative; } ;
struct TYPE_4__ {int /*<<< orphan*/  mods; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int modstack_find (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
set_neg_cache_stats(struct worker* worker, struct ub_server_stats* svr,
	int reset)
{
	int m = modstack_find(&worker->env.mesh->mods, "validator");
	struct val_env* ve;
	struct val_neg_cache* neg;
	if(m == -1)
		return;
	ve = (struct val_env*)worker->env.modinfo[m];
	if(!ve->neg_cache)
		return;
	neg = ve->neg_cache;
	lock_basic_lock(&neg->lock);
	svr->num_neg_cache_noerror = (long long)neg->num_neg_cache_noerror;
	svr->num_neg_cache_nxdomain = (long long)neg->num_neg_cache_nxdomain;
	if(reset && !worker->env.cfg->stat_cumulative) {
		neg->num_neg_cache_noerror = 0;
		neg->num_neg_cache_nxdomain = 0;
	}
	lock_basic_unlock(&neg->lock);
}