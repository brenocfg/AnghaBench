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
typedef  int /*<<< orphan*/  EX_CALLBACKS ;

/* Variables and functions */
 int CRYPTO_EX_INDEX__COUNT ; 
 int /*<<< orphan*/  CRYPTO_F_GET_AND_LOCK ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_PASSED_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_ex_data_init ; 
 int /*<<< orphan*/ * ex_data ; 
 int /*<<< orphan*/  ex_data_init ; 
 int /*<<< orphan*/ * ex_data_lock ; 

__attribute__((used)) static EX_CALLBACKS *get_and_lock(int class_index)
{
    EX_CALLBACKS *ip;

    if (class_index < 0 || class_index >= CRYPTO_EX_INDEX__COUNT) {
        CRYPTOerr(CRYPTO_F_GET_AND_LOCK, ERR_R_PASSED_INVALID_ARGUMENT);
        return NULL;
    }

    if (!RUN_ONCE(&ex_data_init, do_ex_data_init)) {
        CRYPTOerr(CRYPTO_F_GET_AND_LOCK, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    if (ex_data_lock == NULL) {
        /*
         * This can happen in normal operation when using CRYPTO_mem_leaks().
         * The CRYPTO_mem_leaks() function calls OPENSSL_cleanup() which cleans
         * up the locks. Subsequently the BIO that CRYPTO_mem_leaks() uses gets
         * freed, which also attempts to free the ex_data. However
         * CRYPTO_mem_leaks() ensures that the ex_data is freed early (i.e.
         * before OPENSSL_cleanup() is called), so if we get here we can safely
         * ignore this operation. We just treat it as an error.
         */
         return NULL;
    }

    ip = &ex_data[class_index];
    CRYPTO_THREAD_write_lock(ex_data_lock);
    return ip;
}