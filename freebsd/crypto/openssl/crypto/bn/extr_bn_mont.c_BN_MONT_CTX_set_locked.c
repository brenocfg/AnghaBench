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
typedef  int /*<<< orphan*/  CRYPTO_RWLOCK ;
typedef  int /*<<< orphan*/  BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_MONT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_MONT_CTX_new () ; 
 int /*<<< orphan*/  BN_MONT_CTX_set (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ *) ; 

BN_MONT_CTX *BN_MONT_CTX_set_locked(BN_MONT_CTX **pmont, CRYPTO_RWLOCK *lock,
                                    const BIGNUM *mod, BN_CTX *ctx)
{
    BN_MONT_CTX *ret;

    CRYPTO_THREAD_read_lock(lock);
    ret = *pmont;
    CRYPTO_THREAD_unlock(lock);
    if (ret)
        return ret;

    /*
     * We don't want to serialise globally while doing our lazy-init math in
     * BN_MONT_CTX_set. That punishes threads that are doing independent
     * things. Instead, punish the case where more than one thread tries to
     * lazy-init the same 'pmont', by having each do the lazy-init math work
     * independently and only use the one from the thread that wins the race
     * (the losers throw away the work they've done).
     */
    ret = BN_MONT_CTX_new();
    if (ret == NULL)
        return NULL;
    if (!BN_MONT_CTX_set(ret, mod, ctx)) {
        BN_MONT_CTX_free(ret);
        return NULL;
    }

    /* The locked compare-and-set, after the local work is done. */
    CRYPTO_THREAD_write_lock(lock);
    if (*pmont) {
        BN_MONT_CTX_free(ret);
        ret = *pmont;
    } else
        *pmont = ret;
    CRYPTO_THREAD_unlock(lock);
    return ret;
}