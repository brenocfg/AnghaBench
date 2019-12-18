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
struct val_env {int /*<<< orphan*/  num_rrset_bogus; int /*<<< orphan*/  bogus_lock; } ;
struct module_env {int need_to_validate; int /*<<< orphan*/  cfg; void** modinfo; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  ecdsa_evp_workaround_init () ; 
 int /*<<< orphan*/  lock_basic_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_protect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  val_apply_cfg (struct module_env*,struct val_env*,int /*<<< orphan*/ ) ; 

int
val_init(struct module_env* env, int id)
{
	struct val_env* val_env = (struct val_env*)calloc(1,
		sizeof(struct val_env));
	if(!val_env) {
		log_err("malloc failure");
		return 0;
	}
	env->modinfo[id] = (void*)val_env;
	env->need_to_validate = 1;
	lock_basic_init(&val_env->bogus_lock);
	lock_protect(&val_env->bogus_lock, &val_env->num_rrset_bogus,
		sizeof(val_env->num_rrset_bogus));
#ifdef USE_ECDSA_EVP_WORKAROUND
	ecdsa_evp_workaround_init();
#endif
	if(!val_apply_cfg(env, val_env, env->cfg)) {
		log_err("validator: could not apply configuration settings.");
		return 0;
	}

	return 1;
}