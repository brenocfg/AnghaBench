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
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,...) ; 
 int BXE_PREV_WAIT_NEEDED ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_REQ_WOL_DIS ; 
 int FW_MSG_CODE_DRV_UNLOAD_COMMON ; 
 int HW_LOCK_RESOURCE_NVRAM ; 
 int MCPR_ACCESS_LOCK_LOCK ; 
 int MCPR_NVM_SW_ARB_ARB_REQ_CLR1 ; 
 int MCP_REG_MCPR_ACCESS_LOCK ; 
 int MCP_REG_MCPR_NVM_SW_ARB ; 
 int MISC_REG_DRIVER_CONTROL_1 ; 
 int MISC_REG_DRIVER_CONTROL_7 ; 
 int REG_RD (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 
 int SC_FUNC (struct bxe_softc*) ; 
 int SC_PORT (struct bxe_softc*) ; 
 int bxe_fw_command (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_prev_interrupted_dmae (struct bxe_softc*) ; 
 int bxe_prev_unload_common (struct bxe_softc*) ; 
 int bxe_prev_unload_uncommon (struct bxe_softc*) ; 

__attribute__((used)) static int
bxe_prev_unload(struct bxe_softc *sc)
{
    int time_counter = 10;
    uint32_t fw, hw_lock_reg, hw_lock_val;
    uint32_t rc = 0;

    /*
     * Clear HW from errors which may have resulted from an interrupted
     * DMAE transaction.
     */
    bxe_prev_interrupted_dmae(sc);

    /* Release previously held locks */
    hw_lock_reg =
        (SC_FUNC(sc) <= 5) ?
            (MISC_REG_DRIVER_CONTROL_1 + SC_FUNC(sc) * 8) :
            (MISC_REG_DRIVER_CONTROL_7 + (SC_FUNC(sc) - 6) * 8);

    hw_lock_val = (REG_RD(sc, hw_lock_reg));
    if (hw_lock_val) {
        if (hw_lock_val & HW_LOCK_RESOURCE_NVRAM) {
            BLOGD(sc, DBG_LOAD, "Releasing previously held NVRAM lock\n");
            REG_WR(sc, MCP_REG_MCPR_NVM_SW_ARB,
                   (MCPR_NVM_SW_ARB_ARB_REQ_CLR1 << SC_PORT(sc)));
        }
        BLOGD(sc, DBG_LOAD, "Releasing previously held HW lock\n");
        REG_WR(sc, hw_lock_reg, 0xffffffff);
    } else {
        BLOGD(sc, DBG_LOAD, "No need to release HW/NVRAM locks\n");
    }

    if (MCPR_ACCESS_LOCK_LOCK & REG_RD(sc, MCP_REG_MCPR_ACCESS_LOCK)) {
        BLOGD(sc, DBG_LOAD, "Releasing previously held ALR\n");
        REG_WR(sc, MCP_REG_MCPR_ACCESS_LOCK, 0);
    }

    do {
        /* Lock MCP using an unload request */
        fw = bxe_fw_command(sc, DRV_MSG_CODE_UNLOAD_REQ_WOL_DIS, 0);
        if (!fw) {
            BLOGE(sc, "MCP response failure, aborting\n");
            rc = -1;
            break;
        }

        if (fw == FW_MSG_CODE_DRV_UNLOAD_COMMON) {
            rc = bxe_prev_unload_common(sc);
            break;
        }

        /* non-common reply from MCP night require looping */
        rc = bxe_prev_unload_uncommon(sc);
        if (rc != BXE_PREV_WAIT_NEEDED) {
            break;
        }

        DELAY(20000);
    } while (--time_counter);

    if (!time_counter || rc) {
        BLOGE(sc, "Failed to unload previous driver!"
            " time_counter %d rc %d\n", time_counter, rc);
        rc = -1;
    }

    return (rc);
}