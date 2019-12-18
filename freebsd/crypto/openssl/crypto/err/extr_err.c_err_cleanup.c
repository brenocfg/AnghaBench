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

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_cleanup_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * err_string_lock ; 
 int /*<<< orphan*/  err_thread_local ; 
 int /*<<< orphan*/ * int_error_hash ; 
 int /*<<< orphan*/  lh_ERR_STRING_DATA_free (int /*<<< orphan*/ *) ; 
 scalar_t__ set_err_thread_local ; 

void err_cleanup(void)
{
    if (set_err_thread_local != 0)
        CRYPTO_THREAD_cleanup_local(&err_thread_local);
    CRYPTO_THREAD_lock_free(err_string_lock);
    err_string_lock = NULL;
    lh_ERR_STRING_DATA_free(int_error_hash);
    int_error_hash = NULL;
}