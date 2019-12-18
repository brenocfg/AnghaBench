#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  drbg ;
struct TYPE_18__ {scalar_t__ strength; TYPE_1__* seed_pool; TYPE_12__* parent; int /*<<< orphan*/  reseed_next_counter; int /*<<< orphan*/  secure; } ;
struct TYPE_17__ {int entropy_requested; } ;
struct TYPE_16__ {scalar_t__ strength; int /*<<< orphan*/  reseed_prop_counter; } ;
typedef  TYPE_1__ RAND_POOL ;
typedef  TYPE_2__ RAND_DRBG ;

/* Variables and functions */
 scalar_t__ RAND_DRBG_generate (TYPE_12__*,unsigned char*,size_t,int,unsigned char*,int) ; 
 int /*<<< orphan*/  RAND_F_RAND_DRBG_GET_ENTROPY ; 
 int /*<<< orphan*/  RAND_R_PARENT_STRENGTH_TOO_WEAK ; 
 int /*<<< orphan*/  RAND_R_PREDICTION_RESISTANCE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rand_drbg_lock (TYPE_12__*) ; 
 int /*<<< orphan*/  rand_drbg_unlock (TYPE_12__*) ; 
 size_t rand_pool_acquire_entropy (TYPE_1__*) ; 
 unsigned char* rand_pool_add_begin (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  rand_pool_add_end (TYPE_1__*,size_t,int) ; 
 size_t rand_pool_bytes_needed (TYPE_1__*,int) ; 
 unsigned char* rand_pool_detach (TYPE_1__*) ; 
 size_t rand_pool_entropy_available (TYPE_1__*) ; 
 int /*<<< orphan*/  rand_pool_free (TYPE_1__*) ; 
 size_t rand_pool_length (TYPE_1__*) ; 
 TYPE_1__* rand_pool_new (int,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  tsan_load (int /*<<< orphan*/ *) ; 

size_t rand_drbg_get_entropy(RAND_DRBG *drbg,
                             unsigned char **pout,
                             int entropy, size_t min_len, size_t max_len,
                             int prediction_resistance)
{
    size_t ret = 0;
    size_t entropy_available = 0;
    RAND_POOL *pool;

    if (drbg->parent != NULL && drbg->strength > drbg->parent->strength) {
        /*
         * We currently don't support the algorithm from NIST SP 800-90C
         * 10.1.2 to use a weaker DRBG as source
         */
        RANDerr(RAND_F_RAND_DRBG_GET_ENTROPY, RAND_R_PARENT_STRENGTH_TOO_WEAK);
        return 0;
    }

    if (drbg->seed_pool != NULL) {
        pool = drbg->seed_pool;
        pool->entropy_requested = entropy;
    } else {
        pool = rand_pool_new(entropy, drbg->secure, min_len, max_len);
        if (pool == NULL)
            return 0;
    }

    if (drbg->parent != NULL) {
        size_t bytes_needed = rand_pool_bytes_needed(pool, 1 /*entropy_factor*/);
        unsigned char *buffer = rand_pool_add_begin(pool, bytes_needed);

        if (buffer != NULL) {
            size_t bytes = 0;

            /*
             * Get random data from parent. Include our address as additional input,
             * in order to provide some additional distinction between different
             * DRBG child instances.
             * Our lock is already held, but we need to lock our parent before
             * generating bits from it. (Note: taking the lock will be a no-op
             * if locking if drbg->parent->lock == NULL.)
             */
            rand_drbg_lock(drbg->parent);
            if (RAND_DRBG_generate(drbg->parent,
                                   buffer, bytes_needed,
                                   prediction_resistance,
                                   (unsigned char *)&drbg, sizeof(drbg)) != 0)
                bytes = bytes_needed;
            drbg->reseed_next_counter
                = tsan_load(&drbg->parent->reseed_prop_counter);
            rand_drbg_unlock(drbg->parent);

            rand_pool_add_end(pool, bytes, 8 * bytes);
            entropy_available = rand_pool_entropy_available(pool);
        }

    } else {
        if (prediction_resistance) {
            /*
             * We don't have any entropy sources that comply with the NIST
             * standard to provide prediction resistance (see NIST SP 800-90C,
             * Section 5.4).
             */
            RANDerr(RAND_F_RAND_DRBG_GET_ENTROPY,
                    RAND_R_PREDICTION_RESISTANCE_NOT_SUPPORTED);
            goto err;
        }

        /* Get entropy by polling system entropy sources. */
        entropy_available = rand_pool_acquire_entropy(pool);
    }

    if (entropy_available > 0) {
        ret   = rand_pool_length(pool);
        *pout = rand_pool_detach(pool);
    }

 err:
    if (drbg->seed_pool == NULL)
        rand_pool_free(pool);
    return ret;
}