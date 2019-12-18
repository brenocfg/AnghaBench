#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ (* add ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ;} ;
typedef  int /*<<< orphan*/  RAND_POOL ;
typedef  TYPE_1__ RAND_METHOD ;
typedef  int /*<<< orphan*/  RAND_DRBG ;

/* Variables and functions */
 int RAND_DRBG_STRENGTH ; 
 int /*<<< orphan*/ * RAND_DRBG_get0_master () ; 
 TYPE_1__ const* RAND_OpenSSL () ; 
 int /*<<< orphan*/  RAND_POOL_MAX_LENGTH ; 
 TYPE_1__* RAND_get_rand_method () ; 
 int /*<<< orphan*/  rand_drbg_lock (int /*<<< orphan*/ *) ; 
 int rand_drbg_restart (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rand_drbg_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rand_pool_acquire_entropy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand_pool_buffer (int /*<<< orphan*/ *) ; 
 double rand_pool_entropy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand_pool_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand_pool_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rand_pool_new (int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 

int RAND_poll(void)
{
    int ret = 0;

    RAND_POOL *pool = NULL;

    const RAND_METHOD *meth = RAND_get_rand_method();

    if (meth == RAND_OpenSSL()) {
        /* fill random pool and seed the master DRBG */
        RAND_DRBG *drbg = RAND_DRBG_get0_master();

        if (drbg == NULL)
            return 0;

        rand_drbg_lock(drbg);
        ret = rand_drbg_restart(drbg, NULL, 0, 0);
        rand_drbg_unlock(drbg);

        return ret;

    } else {
        /* fill random pool and seed the current legacy RNG */
        pool = rand_pool_new(RAND_DRBG_STRENGTH, 1,
                             (RAND_DRBG_STRENGTH + 7) / 8,
                             RAND_POOL_MAX_LENGTH);
        if (pool == NULL)
            return 0;

        if (rand_pool_acquire_entropy(pool) == 0)
            goto err;

        if (meth->add == NULL
            || meth->add(rand_pool_buffer(pool),
                         rand_pool_length(pool),
                         (rand_pool_entropy(pool) / 8.0)) == 0)
            goto err;

        ret = 1;
    }

err:
    rand_pool_free(pool);
    return ret;
}