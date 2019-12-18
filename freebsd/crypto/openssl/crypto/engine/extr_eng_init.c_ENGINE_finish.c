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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_F_ENGINE_FINISH ; 
 int /*<<< orphan*/  ENGINE_R_FINISH_FAILED ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int engine_unlocked_finish (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  global_engine_lock ; 

int ENGINE_finish(ENGINE *e)
{
    int to_return = 1;

    if (e == NULL)
        return 1;
    CRYPTO_THREAD_write_lock(global_engine_lock);
    to_return = engine_unlocked_finish(e, 1);
    CRYPTO_THREAD_unlock(global_engine_lock);
    if (!to_return) {
        ENGINEerr(ENGINE_F_ENGINE_FINISH, ENGINE_R_FINISH_FAILED);
        return 0;
    }
    return to_return;
}