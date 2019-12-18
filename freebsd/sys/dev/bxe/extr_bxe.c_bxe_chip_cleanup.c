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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ecore_mcast_ramrod_params {int /*<<< orphan*/ * mcast_obj; int /*<<< orphan*/ * member_0; } ;
struct bxe_softc {int num_queues; int /*<<< orphan*/  mcast_obj; int /*<<< orphan*/  sp_state; TYPE_1__* sp_objs; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  BXE_MCAST_LOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  BXE_MCAST_UNLOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  CHIP_IS_E1 (struct bxe_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ECORE_ETH_MAC ; 
 int /*<<< orphan*/  ECORE_FILTER_RX_MODE_PENDING ; 
 int /*<<< orphan*/  ECORE_FILTER_RX_MODE_SCHED ; 
 int /*<<< orphan*/  ECORE_MCAST_CMD_DEL ; 
 int /*<<< orphan*/  ECORE_UC_LIST_MAC ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NIG_REG_LLH0_FUNC_EN ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int SC_PORT (struct bxe_softc*) ; 
 int /*<<< orphan*/  TRUE ; 
 int bxe_del_all_macs (struct bxe_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_drain_tx_queues (struct bxe_softc*) ; 
 int bxe_func_stop (struct bxe_softc*) ; 
 int bxe_func_wait_started (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_int_disable_sync (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_interrupt_detach (struct bxe_softc*) ; 
 int bxe_reset_hw (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_send_unload_done (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_send_unload_req (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bxe_set_storm_rx_mode (struct bxe_softc*) ; 
 scalar_t__ bxe_stop_queue (struct bxe_softc*,int) ; 
 scalar_t__ bxe_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bxe_wait_sp_comp (struct bxe_softc*,int) ; 
 int ecore_config_mcast (struct bxe_softc*,struct ecore_mcast_ramrod_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_chip_cleanup(struct bxe_softc *sc,
                 uint32_t         unload_mode,
                 uint8_t          keep_link)
{
    int port = SC_PORT(sc);
    struct ecore_mcast_ramrod_params rparam = { NULL };
    uint32_t reset_code;
    int i, rc = 0;

    bxe_drain_tx_queues(sc);

    /* give HW time to discard old tx messages */
    DELAY(1000);

    /* Clean all ETH MACs */
    rc = bxe_del_all_macs(sc, &sc->sp_objs[0].mac_obj, ECORE_ETH_MAC, FALSE);
    if (rc < 0) {
        BLOGE(sc, "Failed to delete all ETH MACs (%d)\n", rc);
    }

    /* Clean up UC list  */
    rc = bxe_del_all_macs(sc, &sc->sp_objs[0].mac_obj, ECORE_UC_LIST_MAC, TRUE);
    if (rc < 0) {
        BLOGE(sc, "Failed to delete UC MACs list (%d)\n", rc);
    }

    /* Disable LLH */
    if (!CHIP_IS_E1(sc)) {
        REG_WR(sc, NIG_REG_LLH0_FUNC_EN + port*8, 0);
    }

    /* Set "drop all" to stop Rx */

    /*
     * We need to take the BXE_MCAST_LOCK() here in order to prevent
     * a race between the completion code and this code.
     */
    BXE_MCAST_LOCK(sc);

    if (bxe_test_bit(ECORE_FILTER_RX_MODE_PENDING, &sc->sp_state)) {
        bxe_set_bit(ECORE_FILTER_RX_MODE_SCHED, &sc->sp_state);
    } else {
        bxe_set_storm_rx_mode(sc);
    }

    /* Clean up multicast configuration */
    rparam.mcast_obj = &sc->mcast_obj;
    rc = ecore_config_mcast(sc, &rparam, ECORE_MCAST_CMD_DEL);
    if (rc < 0) {
        BLOGE(sc, "Failed to send DEL MCAST command (%d)\n", rc);
    }

    BXE_MCAST_UNLOCK(sc);

    // XXX bxe_iov_chip_cleanup(sc);

    /*
     * Send the UNLOAD_REQUEST to the MCP. This will return if
     * this function should perform FUNCTION, PORT, or COMMON HW
     * reset.
     */
    reset_code = bxe_send_unload_req(sc, unload_mode);

    /*
     * (assumption: No Attention from MCP at this stage)
     * PMF probably in the middle of TX disable/enable transaction
     */
    rc = bxe_func_wait_started(sc);
    if (rc) {
        BLOGE(sc, "bxe_func_wait_started failed (%d)\n", rc);
    }

    /*
     * Close multi and leading connections
     * Completions for ramrods are collected in a synchronous way
     */
    for (i = 0; i < sc->num_queues; i++) {
        if (bxe_stop_queue(sc, i)) {
            goto unload_error;
        }
    }

    /*
     * If SP settings didn't get completed so far - something
     * very wrong has happen.
     */
    if (!bxe_wait_sp_comp(sc, ~0x0UL)) {
        BLOGE(sc, "Common slow path ramrods got stuck!(%d)\n", rc);
    }

unload_error:

    rc = bxe_func_stop(sc);
    if (rc) {
        BLOGE(sc, "Function stop failed!(%d)\n", rc);
    }

    /* disable HW interrupts */
    bxe_int_disable_sync(sc, TRUE);

    /* detach interrupts */
    bxe_interrupt_detach(sc);

    /* Reset the chip */
    rc = bxe_reset_hw(sc, reset_code);
    if (rc) {
        BLOGE(sc, "Hardware reset failed(%d)\n", rc);
    }

    /* Report UNLOAD_DONE to MCP */
    bxe_send_unload_done(sc, keep_link);
}