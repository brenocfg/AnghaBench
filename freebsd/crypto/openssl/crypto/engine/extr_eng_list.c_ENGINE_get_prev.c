#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  struct_ref; struct TYPE_6__* prev; } ;
typedef  TYPE_1__ ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_F_ENGINE_GET_PREV ; 
 int /*<<< orphan*/  ENGINE_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  engine_ref_debug (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  global_engine_lock ; 

ENGINE *ENGINE_get_prev(ENGINE *e)
{
    ENGINE *ret = NULL;
    if (e == NULL) {
        ENGINEerr(ENGINE_F_ENGINE_GET_PREV, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    CRYPTO_THREAD_write_lock(global_engine_lock);
    ret = e->prev;
    if (ret) {
        /* Return a valid structural reference to the next ENGINE */
        ret->struct_ref++;
        engine_ref_debug(ret, 0, 1);
    }
    CRYPTO_THREAD_unlock(global_engine_lock);
    /* Release the structural reference to the previous ENGINE */
    ENGINE_free(e);
    return ret;
}