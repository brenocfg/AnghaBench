#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int secure; scalar_t__ strength; int /*<<< orphan*/  reseed_time_interval; int /*<<< orphan*/  reseed_interval; void* cleanup_entropy; void* get_entropy; int /*<<< orphan*/  cleanup_nonce; int /*<<< orphan*/  get_nonce; struct TYPE_11__* parent; int /*<<< orphan*/  fork_id; } ;
typedef  TYPE_1__ RAND_DRBG ;

/* Variables and functions */
 scalar_t__ CRYPTO_secure_allocated (TYPE_1__*) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_secure_zalloc (int) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  RAND_DRBG_free (TYPE_1__*) ; 
 scalar_t__ RAND_DRBG_set (TYPE_1__*,int,unsigned int) ; 
 int /*<<< orphan*/  RAND_F_RAND_DRBG_NEW ; 
 int /*<<< orphan*/  RAND_R_PARENT_STRENGTH_TOO_WEAK ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  master_reseed_interval ; 
 int /*<<< orphan*/  master_reseed_time_interval ; 
 int /*<<< orphan*/  openssl_get_fork_id () ; 
 void* rand_drbg_cleanup_entropy ; 
 int /*<<< orphan*/  rand_drbg_cleanup_nonce ; 
 void* rand_drbg_get_entropy ; 
 int /*<<< orphan*/  rand_drbg_get_nonce ; 
 int /*<<< orphan*/  rand_drbg_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  rand_drbg_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  slave_reseed_interval ; 
 int /*<<< orphan*/  slave_reseed_time_interval ; 

__attribute__((used)) static RAND_DRBG *rand_drbg_new(int secure,
                                int type,
                                unsigned int flags,
                                RAND_DRBG *parent)
{
    RAND_DRBG *drbg = secure ? OPENSSL_secure_zalloc(sizeof(*drbg))
                             : OPENSSL_zalloc(sizeof(*drbg));

    if (drbg == NULL) {
        RANDerr(RAND_F_RAND_DRBG_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    drbg->secure = secure && CRYPTO_secure_allocated(drbg);
    drbg->fork_id = openssl_get_fork_id();
    drbg->parent = parent;

    if (parent == NULL) {
        drbg->get_entropy = rand_drbg_get_entropy;
        drbg->cleanup_entropy = rand_drbg_cleanup_entropy;
#ifndef RAND_DRBG_GET_RANDOM_NONCE
        drbg->get_nonce = rand_drbg_get_nonce;
        drbg->cleanup_nonce = rand_drbg_cleanup_nonce;
#endif

        drbg->reseed_interval = master_reseed_interval;
        drbg->reseed_time_interval = master_reseed_time_interval;
    } else {
        drbg->get_entropy = rand_drbg_get_entropy;
        drbg->cleanup_entropy = rand_drbg_cleanup_entropy;
        /*
         * Do not provide nonce callbacks, the child DRBGs will
         * obtain their nonce using random bits from the parent.
         */

        drbg->reseed_interval = slave_reseed_interval;
        drbg->reseed_time_interval = slave_reseed_time_interval;
    }

    if (RAND_DRBG_set(drbg, type, flags) == 0)
        goto err;

    if (parent != NULL) {
        rand_drbg_lock(parent);
        if (drbg->strength > parent->strength) {
            /*
             * We currently don't support the algorithm from NIST SP 800-90C
             * 10.1.2 to use a weaker DRBG as source
             */
            rand_drbg_unlock(parent);
            RANDerr(RAND_F_RAND_DRBG_NEW, RAND_R_PARENT_STRENGTH_TOO_WEAK);
            goto err;
        }
        rand_drbg_unlock(parent);
    }

    return drbg;

 err:
    RAND_DRBG_free(drbg);

    return NULL;
}