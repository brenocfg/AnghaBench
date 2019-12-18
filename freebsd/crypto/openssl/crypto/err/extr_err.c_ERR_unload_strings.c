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
struct TYPE_4__ {scalar_t__ error; } ;
typedef  TYPE_1__ ERR_STRING_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_err_strings_init ; 
 int /*<<< orphan*/  err_string_init ; 
 int /*<<< orphan*/  err_string_lock ; 
 int /*<<< orphan*/  int_error_hash ; 
 int /*<<< orphan*/  lh_ERR_STRING_DATA_delete (int /*<<< orphan*/ ,TYPE_1__*) ; 

int ERR_unload_strings(int lib, ERR_STRING_DATA *str)
{
    if (!RUN_ONCE(&err_string_init, do_err_strings_init))
        return 0;

    CRYPTO_THREAD_write_lock(err_string_lock);
    /*
     * We don't need to ERR_PACK the lib, since that was done (to
     * the table) when it was loaded.
     */
    for (; str->error; str++)
        (void)lh_ERR_STRING_DATA_delete(int_error_hash, str);
    CRYPTO_THREAD_unlock(err_string_lock);

    return 1;
}