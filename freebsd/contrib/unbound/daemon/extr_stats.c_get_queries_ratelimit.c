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
struct TYPE_6__ {TYPE_1__* cfg; scalar_t__* modinfo; TYPE_2__* mesh; } ;
struct worker {TYPE_3__ env; } ;
struct iter_env {size_t num_queries_ratelimited; int /*<<< orphan*/  queries_ratelimit_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  mods; } ;
struct TYPE_4__ {int /*<<< orphan*/  stat_cumulative; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int modstack_find (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static size_t
get_queries_ratelimit(struct worker* worker, int reset)
{
	int m = modstack_find(&worker->env.mesh->mods, "iterator");
	struct iter_env* ie;
	size_t r;
	if(m == -1)
		return 0;
	ie = (struct iter_env*)worker->env.modinfo[m];
	lock_basic_lock(&ie->queries_ratelimit_lock);
	r = ie->num_queries_ratelimited;
	if(reset && !worker->env.cfg->stat_cumulative)
		ie->num_queries_ratelimited = 0;
	lock_basic_unlock(&ie->queries_ratelimit_lock);
	return r;
}