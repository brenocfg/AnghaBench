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
struct dnsc_env {int /*<<< orphan*/  nonces_cache_lock; void* nonces_cache; void* shared_secrets_cache; int /*<<< orphan*/  shared_secrets_cache_lock; int /*<<< orphan*/  provider_name; int /*<<< orphan*/  hash_key; } ;
struct config_file {int /*<<< orphan*/  dnscrypt_nonce_cache_size; int /*<<< orphan*/  dnscrypt_nonce_cache_slabs; int /*<<< orphan*/  dnscrypt_shared_secret_cache_size; int /*<<< orphan*/  dnscrypt_shared_secret_cache_slabs; int /*<<< orphan*/  dnscrypt_provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_DEFAULT_STARTARRAY ; 
 scalar_t__ dnsc_load_local_data (struct dnsc_env*,struct config_file*) ; 
 int /*<<< orphan*/  dnsc_nonces_compfunc ; 
 int /*<<< orphan*/  dnsc_nonces_deldatafunc ; 
 int /*<<< orphan*/  dnsc_nonces_delkeyfunc ; 
 int /*<<< orphan*/  dnsc_nonces_sizefunc ; 
 scalar_t__ dnsc_parse_certs (struct dnsc_env*,struct config_file*) ; 
 scalar_t__ dnsc_parse_keys (struct dnsc_env*,struct config_file*) ; 
 int /*<<< orphan*/  dnsc_shared_secrets_compfunc ; 
 int /*<<< orphan*/  dnsc_shared_secrets_deldatafunc ; 
 int /*<<< orphan*/  dnsc_shared_secrets_delkeyfunc ; 
 int /*<<< orphan*/  dnsc_shared_secrets_sizefunc ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  randombytes_buf (int /*<<< orphan*/ ,int) ; 
 void* slabhash_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
dnsc_apply_cfg(struct dnsc_env *env, struct config_file *cfg)
{
    if(dnsc_parse_certs(env, cfg) <= 0) {
        fatal_exit("dnsc_apply_cfg: no cert file loaded");
    }
    if(dnsc_parse_keys(env, cfg) <= 0) {
        fatal_exit("dnsc_apply_cfg: no key file loaded");
    }
    randombytes_buf(env->hash_key, sizeof env->hash_key);
    env->provider_name = cfg->dnscrypt_provider;

    if(dnsc_load_local_data(env, cfg) <= 0) {
        fatal_exit("dnsc_apply_cfg: could not load local data");
    }
    lock_basic_lock(&env->shared_secrets_cache_lock);
    env->shared_secrets_cache = slabhash_create(
        cfg->dnscrypt_shared_secret_cache_slabs,
        HASH_DEFAULT_STARTARRAY,
        cfg->dnscrypt_shared_secret_cache_size,
        dnsc_shared_secrets_sizefunc,
        dnsc_shared_secrets_compfunc,
        dnsc_shared_secrets_delkeyfunc,
        dnsc_shared_secrets_deldatafunc,
        NULL
    );
    lock_basic_unlock(&env->shared_secrets_cache_lock);
    if(!env->shared_secrets_cache){
        fatal_exit("dnsc_apply_cfg: could not create shared secrets cache.");
    }
    lock_basic_lock(&env->nonces_cache_lock);
    env->nonces_cache = slabhash_create(
        cfg->dnscrypt_nonce_cache_slabs,
        HASH_DEFAULT_STARTARRAY,
        cfg->dnscrypt_nonce_cache_size,
        dnsc_nonces_sizefunc,
        dnsc_nonces_compfunc,
        dnsc_nonces_delkeyfunc,
        dnsc_nonces_deldatafunc,
        NULL
    );
    lock_basic_unlock(&env->nonces_cache_lock);
    return 0;
}