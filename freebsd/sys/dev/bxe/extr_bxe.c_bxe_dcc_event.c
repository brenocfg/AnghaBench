#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int* mf_config; } ;
struct TYPE_4__ {TYPE_1__ mf_info; } ;
struct bxe_softc {int /*<<< orphan*/  flags; TYPE_2__ devinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BXE_MF_FUNC_DIS ; 
 int /*<<< orphan*/  DBG_INTR ; 
 int /*<<< orphan*/  DRV_MSG_CODE_DCC_FAILURE ; 
 int /*<<< orphan*/  DRV_MSG_CODE_DCC_OK ; 
 int DRV_STATUS_DCC_BANDWIDTH_ALLOCATION ; 
 int DRV_STATUS_DCC_DISABLE_ENABLE_PF ; 
 int FUNC_MF_CFG_FUNC_DISABLED ; 
 size_t SC_VN (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_config_mf_bw (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_e1h_disable (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_e1h_enable (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_fw_command (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_dcc_event(struct bxe_softc *sc,
              uint32_t         dcc_event)
{
    BLOGD(sc, DBG_INTR, "dcc_event 0x%08x\n", dcc_event);

    if (dcc_event & DRV_STATUS_DCC_DISABLE_ENABLE_PF) {
        /*
         * This is the only place besides the function initialization
         * where the sc->flags can change so it is done without any
         * locks
         */
        if (sc->devinfo.mf_info.mf_config[SC_VN(sc)] & FUNC_MF_CFG_FUNC_DISABLED) {
            BLOGD(sc, DBG_INTR, "mf_cfg function disabled\n");
            sc->flags |= BXE_MF_FUNC_DIS;
            bxe_e1h_disable(sc);
        } else {
            BLOGD(sc, DBG_INTR, "mf_cfg function enabled\n");
            sc->flags &= ~BXE_MF_FUNC_DIS;
            bxe_e1h_enable(sc);
        }
        dcc_event &= ~DRV_STATUS_DCC_DISABLE_ENABLE_PF;
    }

    if (dcc_event & DRV_STATUS_DCC_BANDWIDTH_ALLOCATION) {
        bxe_config_mf_bw(sc);
        dcc_event &= ~DRV_STATUS_DCC_BANDWIDTH_ALLOCATION;
    }

    /* Report results to MCP */
    if (dcc_event)
        bxe_fw_command(sc, DRV_MSG_CODE_DCC_FAILURE, 0);
    else
        bxe_fw_command(sc, DRV_MSG_CODE_DCC_OK, 0);
}