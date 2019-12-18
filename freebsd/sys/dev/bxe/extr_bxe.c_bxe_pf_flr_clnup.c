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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER ; 
 int /*<<< orphan*/  PGLUE_B_REG_INTERNAL_PFID_ENABLE_TARGET_READ ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SC_ABS_FUNC (struct bxe_softc*) ; 
 scalar_t__ SC_FUNC (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_flr_clnup_poll_count (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_hw_enable_status (struct bxe_softc*) ; 
 scalar_t__ bxe_is_pcie_pending (struct bxe_softc*) ; 
 scalar_t__ bxe_poll_hw_usage_counters (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ bxe_send_final_clnup (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_tx_hw_flushed (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_pf_flr_clnup(struct bxe_softc *sc)
{
    uint32_t poll_cnt = bxe_flr_clnup_poll_count(sc);

    BLOGD(sc, DBG_LOAD, "Cleanup after FLR PF[%d]\n", SC_ABS_FUNC(sc));

    /* Re-enable PF target read access */
    REG_WR(sc, PGLUE_B_REG_INTERNAL_PFID_ENABLE_TARGET_READ, 1);

    /* Poll HW usage counters */
    BLOGD(sc, DBG_LOAD, "Polling usage counters\n");
    if (bxe_poll_hw_usage_counters(sc, poll_cnt)) {
        return (-1);
    }

    /* Zero the igu 'trailing edge' and 'leading edge' */

    /* Send the FW cleanup command */
    if (bxe_send_final_clnup(sc, (uint8_t)SC_FUNC(sc), poll_cnt)) {
        return (-1);
    }

    /* ATC cleanup */

    /* Verify TX hw is flushed */
    bxe_tx_hw_flushed(sc, poll_cnt);

    /* Wait 100ms (not adjusted according to platform) */
    DELAY(100000);

    /* Verify no pending pci transactions */
    if (bxe_is_pcie_pending(sc)) {
        BLOGE(sc, "PCIE Transactions still pending\n");
    }

    /* Debug */
    bxe_hw_enable_status(sc);

    /*
     * Master enable - Due to WB DMAE writes performed before this
     * register is re-initialized as part of the regular function init
     */
    REG_WR(sc, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 1);

    return (0);
}