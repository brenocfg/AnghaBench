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
typedef  int /*<<< orphan*/  RAND_DRBG ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_get_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_INIT_THREAD_RAND ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_rand_drbg_init ; 
 int /*<<< orphan*/ * drbg_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  master_drbg ; 
 int /*<<< orphan*/  ossl_init_thread_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  private_drbg ; 
 int /*<<< orphan*/  rand_drbg_init ; 

RAND_DRBG *RAND_DRBG_get0_private(void)
{
    RAND_DRBG *drbg;

    if (!RUN_ONCE(&rand_drbg_init, do_rand_drbg_init))
        return NULL;

    drbg = CRYPTO_THREAD_get_local(&private_drbg);
    if (drbg == NULL) {
        if (!ossl_init_thread_start(OPENSSL_INIT_THREAD_RAND))
            return NULL;
        drbg = drbg_setup(master_drbg);
        CRYPTO_THREAD_set_local(&private_drbg, drbg);
    }
    return drbg;
}