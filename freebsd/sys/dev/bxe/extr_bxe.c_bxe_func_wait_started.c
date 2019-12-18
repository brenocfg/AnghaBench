#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ecore_func_state_params {int /*<<< orphan*/  cmd; int /*<<< orphan*/  ramrod_flags; int /*<<< orphan*/ * f_obj; int /*<<< orphan*/ * member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  pmf; } ;
struct bxe_softc {int /*<<< orphan*/  func_obj; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ECORE_F_CMD_TX_START ; 
 int /*<<< orphan*/  ECORE_F_CMD_TX_STOP ; 
 scalar_t__ ECORE_F_STATE_STARTED ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 
 int /*<<< orphan*/  bxe_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ecore_func_get_state (struct bxe_softc*,int /*<<< orphan*/ *) ; 
 int ecore_func_state_change (struct bxe_softc*,struct ecore_func_state_params*) ; 

__attribute__((used)) static int
bxe_func_wait_started(struct bxe_softc *sc)
{
    int tout = 50;

    if (!sc->port.pmf) {
        return (0);
    }

    /*
     * (assumption: No Attention from MCP at this stage)
     * PMF probably in the middle of TX disable/enable transaction
     * 1. Sync IRS for default SB
     * 2. Sync SP queue - this guarantees us that attention handling started
     * 3. Wait, that TX disable/enable transaction completes
     *
     * 1+2 guarantee that if DCBX attention was scheduled it already changed
     * pending bit of transaction from STARTED-->TX_STOPPED, if we already
     * received completion for the transaction the state is TX_STOPPED.
     * State will return to STARTED after completion of TX_STOPPED-->STARTED
     * transaction.
     */

    /* XXX make sure default SB ISR is done */
    /* need a way to synchronize an irq (intr_mtx?) */

    /* XXX flush any work queues */

    while (ecore_func_get_state(sc, &sc->func_obj) !=
           ECORE_F_STATE_STARTED && tout--) {
        DELAY(20000);
    }

    if (ecore_func_get_state(sc, &sc->func_obj) != ECORE_F_STATE_STARTED) {
        /*
         * Failed to complete the transaction in a "good way"
         * Force both transactions with CLR bit.
         */
        struct ecore_func_state_params func_params = { NULL };

        BLOGE(sc, "Unexpected function state! "
                  "Forcing STARTED-->TX_STOPPED-->STARTED\n");

        func_params.f_obj = &sc->func_obj;
        bxe_set_bit(RAMROD_DRV_CLR_ONLY, &func_params.ramrod_flags);

        /* STARTED-->TX_STOPPED */
        func_params.cmd = ECORE_F_CMD_TX_STOP;
        ecore_func_state_change(sc, &func_params);

        /* TX_STOPPED-->STARTED */
        func_params.cmd = ECORE_F_CMD_TX_START;
        return (ecore_func_state_change(sc, &func_params));
    }

    return (0);
}