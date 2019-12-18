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
struct module_env {int /*<<< orphan*/  cfg; void** modinfo; } ;
struct iter_env {int /*<<< orphan*/  num_queries_ratelimited; int /*<<< orphan*/  queries_ratelimit_lock; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  iter_apply_cfg (struct iter_env*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_protect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  log_err (char*) ; 

int 
iter_init(struct module_env* env, int id)
{
	struct iter_env* iter_env = (struct iter_env*)calloc(1,
		sizeof(struct iter_env));
	if(!iter_env) {
		log_err("malloc failure");
		return 0;
	}
	env->modinfo[id] = (void*)iter_env;

	lock_basic_init(&iter_env->queries_ratelimit_lock);
	lock_protect(&iter_env->queries_ratelimit_lock,
			&iter_env->num_queries_ratelimited,
		sizeof(iter_env->num_queries_ratelimited));

	if(!iter_apply_cfg(iter_env, env->cfg)) {
		log_err("iterator: could not apply configuration settings.");
		return 0;
	}

	return 1;
}