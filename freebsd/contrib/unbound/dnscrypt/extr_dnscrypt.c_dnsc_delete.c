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
struct dnsc_env {int /*<<< orphan*/  nonces_cache; int /*<<< orphan*/  shared_secrets_cache; int /*<<< orphan*/  nonces_cache_lock; int /*<<< orphan*/  shared_secrets_cache_lock; int /*<<< orphan*/  keypairs; int /*<<< orphan*/  certs; int /*<<< orphan*/  rotated_certs; int /*<<< orphan*/  signed_certs; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_OPS ; 
 int /*<<< orphan*/  free (struct dnsc_env*) ; 
 int /*<<< orphan*/  lock_basic_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slabhash_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sodium_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

void
dnsc_delete(struct dnsc_env *env)
{
	if(!env) {
		return;
	}
	verbose(VERB_OPS, "DNSCrypt: Freeing environment.");
	sodium_free(env->signed_certs);
	sodium_free(env->rotated_certs);
	sodium_free(env->certs);
	sodium_free(env->keypairs);
	lock_basic_destroy(&env->shared_secrets_cache_lock);
	lock_basic_destroy(&env->nonces_cache_lock);
	slabhash_delete(env->shared_secrets_cache);
	slabhash_delete(env->nonces_cache);
	free(env);
}