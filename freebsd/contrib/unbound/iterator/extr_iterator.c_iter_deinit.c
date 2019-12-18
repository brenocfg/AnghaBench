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
struct module_env {int /*<<< orphan*/ ** modinfo; } ;
struct iter_env {struct iter_env* caps_white; int /*<<< orphan*/  donotq; int /*<<< orphan*/  priv; struct iter_env* target_fetch_policy; int /*<<< orphan*/  queries_ratelimit_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  caps_free ; 
 int /*<<< orphan*/  donotq_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct iter_env*) ; 
 int /*<<< orphan*/  lock_basic_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  priv_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traverse_postorder (struct iter_env*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void 
iter_deinit(struct module_env* env, int id)
{
	struct iter_env* iter_env;
	if(!env || !env->modinfo[id])
		return;
	iter_env = (struct iter_env*)env->modinfo[id];
	lock_basic_destroy(&iter_env->queries_ratelimit_lock);
	free(iter_env->target_fetch_policy);
	priv_delete(iter_env->priv);
	donotq_delete(iter_env->donotq);
	if(iter_env->caps_white) {
		traverse_postorder(iter_env->caps_white, caps_free, NULL);
		free(iter_env->caps_white);
	}
	free(iter_env);
	env->modinfo[id] = NULL;
}