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
struct val_env {struct val_env* nsec3_maxiter; struct val_env* nsec3_keysize; int /*<<< orphan*/  neg_cache; int /*<<< orphan*/  kcache; int /*<<< orphan*/  bogus_lock; } ;
struct module_env {int /*<<< orphan*/ ** modinfo; int /*<<< orphan*/ * anchors; } ;

/* Variables and functions */
 int /*<<< orphan*/  anchors_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct val_env*) ; 
 int /*<<< orphan*/  key_cache_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neg_cache_delete (int /*<<< orphan*/ ) ; 

void
val_deinit(struct module_env* env, int id)
{
	struct val_env* val_env;
	if(!env || !env->modinfo[id])
		return;
	val_env = (struct val_env*)env->modinfo[id];
	lock_basic_destroy(&val_env->bogus_lock);
	anchors_delete(env->anchors);
	env->anchors = NULL;
	key_cache_delete(val_env->kcache);
	neg_cache_delete(val_env->neg_cache);
	free(val_env->nsec3_keysize);
	free(val_env->nsec3_maxiter);
	free(val_env);
	env->modinfo[id] = NULL;
}