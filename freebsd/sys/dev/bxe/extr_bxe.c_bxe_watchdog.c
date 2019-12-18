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
struct bxe_softc {int /*<<< orphan*/  sp_err_timeout_task; } ;
struct bxe_fastpath {scalar_t__ watchdog_timer; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXE_ERR_TXQ_STUCK ; 
 int /*<<< orphan*/  BXE_FP_TX_LOCK (struct bxe_fastpath*) ; 
 int /*<<< orphan*/  BXE_FP_TX_UNLOCK (struct bxe_fastpath*) ; 
 int /*<<< orphan*/  BXE_SET_ERROR_BIT (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  taskqueue_enqueue_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static int
bxe_watchdog(struct bxe_softc    *sc,
             struct bxe_fastpath *fp)
{
    BXE_FP_TX_LOCK(fp);

    if ((fp->watchdog_timer == 0) || (--fp->watchdog_timer)) {
        BXE_FP_TX_UNLOCK(fp);
        return (0);
    }

    BLOGE(sc, "TX watchdog timeout on fp[%02d], resetting!\n", fp->index);

    BXE_FP_TX_UNLOCK(fp);
    BXE_SET_ERROR_BIT(sc, BXE_ERR_TXQ_STUCK);
    taskqueue_enqueue_timeout(taskqueue_thread,
        &sc->sp_err_timeout_task, hz/10);

    return (-1);
}