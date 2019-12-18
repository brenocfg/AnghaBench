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
struct dnsc_env {int /*<<< orphan*/  num_query_dnscrypt_replay; int /*<<< orphan*/  nonces_cache_lock; int /*<<< orphan*/  nonces_cache; int /*<<< orphan*/  num_query_dnscrypt_secret_missed_cache; int /*<<< orphan*/  shared_secrets_cache_lock; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int /*<<< orphan*/  lock_basic_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_protect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int sodium_init () ; 
 int /*<<< orphan*/  sodium_misuse_handler ; 
 int /*<<< orphan*/  sodium_set_misuse_handler (int /*<<< orphan*/ ) ; 

struct dnsc_env *
dnsc_create(void)
{
	struct dnsc_env *env;
#ifdef SODIUM_MISUSE_HANDLER
	sodium_set_misuse_handler(sodium_misuse_handler);
#endif
	if (sodium_init() == -1) {
		fatal_exit("dnsc_create: could not initialize libsodium.");
	}
	env = (struct dnsc_env *) calloc(1, sizeof(struct dnsc_env));
	lock_basic_init(&env->shared_secrets_cache_lock);
	lock_protect(&env->shared_secrets_cache_lock,
                 &env->num_query_dnscrypt_secret_missed_cache,
                 sizeof(env->num_query_dnscrypt_secret_missed_cache));
	lock_basic_init(&env->nonces_cache_lock);
	lock_protect(&env->nonces_cache_lock,
                 &env->nonces_cache,
                 sizeof(env->nonces_cache));
	lock_protect(&env->nonces_cache_lock,
                 &env->num_query_dnscrypt_replay,
                 sizeof(env->num_query_dnscrypt_replay));

	return env;
}