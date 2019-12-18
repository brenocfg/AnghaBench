#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {int periodic_flags; } ;
struct TYPE_9__ {scalar_t__ pmf; } ;
struct TYPE_7__ {int /*<<< orphan*/ * mf_config; } ;
struct TYPE_8__ {TYPE_1__ mf_info; } ;
struct bxe_softc {int /*<<< orphan*/  sp_err_timeout_task; TYPE_4__ link_vars; TYPE_3__ port; TYPE_2__ devinfo; } ;
struct TYPE_12__ {int /*<<< orphan*/  drv_status; } ;
struct TYPE_11__ {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,...) ; 
 int /*<<< orphan*/  BXE_ERR_MCP_ASSERT ; 
 int /*<<< orphan*/  BXE_ERR_MC_ASSERT ; 
 int BXE_GRC_RSV ; 
 int BXE_GRC_TIMEOUT ; 
 int BXE_MCP_ASSERT ; 
 int BXE_MC_ASSERT_BITS ; 
 int BXE_PMF_LINK_ASSERT (struct bxe_softc*) ; 
 int /*<<< orphan*/  BXE_SET_ERROR_BIT (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 int DRV_STATUS_DCC_EVENT_MASK ; 
 int DRV_STATUS_DRV_INFO_REQ ; 
 int DRV_STATUS_EEE_NEGOTIATION_RESULTS ; 
 int DRV_STATUS_PMF ; 
 int DRV_STATUS_SET_MF_BW ; 
 int ELINK_PERIODIC_FLAGS_LINK_EVENT ; 
 int EVEREST_GEN_ATTN_IN_USE_MASK ; 
 int EVEREST_LATCHED_ATTN_IN_USE_MASK ; 
 scalar_t__ IS_MF (struct bxe_softc*) ; 
 int /*<<< orphan*/  MFCFG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ MISC_REG_AEU_CLR_LATCH_SIGNAL ; 
 scalar_t__ MISC_REG_AEU_GENERAL_ATTN_10 ; 
 scalar_t__ MISC_REG_AEU_GENERAL_ATTN_11 ; 
 scalar_t__ MISC_REG_AEU_GENERAL_ATTN_12 ; 
 scalar_t__ MISC_REG_AEU_GENERAL_ATTN_7 ; 
 scalar_t__ MISC_REG_AEU_GENERAL_ATTN_8 ; 
 scalar_t__ MISC_REG_AEU_GENERAL_ATTN_9 ; 
 int /*<<< orphan*/  MISC_REG_GRC_RSV_ATTN ; 
 int /*<<< orphan*/  MISC_REG_GRC_TIMEOUT_ATTN ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 
 size_t SC_ABS_FUNC (struct bxe_softc*) ; 
 int SC_FUNC (struct bxe_softc*) ; 
 size_t SC_FW_MB_IDX (struct bxe_softc*) ; 
 size_t SC_VN (struct bxe_softc*) ; 
 int SHMEM_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_acquire_phy_lock (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_dcc_event (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  bxe_handle_drv_info_req (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_handle_eee_event (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_int_disable (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_link_report (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_link_status_update (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_mc_assert (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_pmf_update (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_read_mf_cfg (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_release_phy_lock (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_set_mf_bw (struct bxe_softc*) ; 
 TYPE_6__* func_mb ; 
 TYPE_5__* func_mf_config ; 
 int hz ; 
 int /*<<< orphan*/  taskqueue_enqueue_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static void
bxe_attn_int_deasserted3(struct bxe_softc *sc,
                         uint32_t         attn)
{
    int func = SC_FUNC(sc);
    uint32_t val;

    if (attn & EVEREST_GEN_ATTN_IN_USE_MASK) {

        if (attn & BXE_PMF_LINK_ASSERT(sc)) {

            REG_WR(sc, MISC_REG_AEU_GENERAL_ATTN_12 + func*4, 0);
            bxe_read_mf_cfg(sc);
            sc->devinfo.mf_info.mf_config[SC_VN(sc)] =
                MFCFG_RD(sc, func_mf_config[SC_ABS_FUNC(sc)].config);
            val = SHMEM_RD(sc, func_mb[SC_FW_MB_IDX(sc)].drv_status);

            if (val & DRV_STATUS_DCC_EVENT_MASK)
                bxe_dcc_event(sc, (val & DRV_STATUS_DCC_EVENT_MASK));

            if (val & DRV_STATUS_SET_MF_BW)
                bxe_set_mf_bw(sc);

            if (val & DRV_STATUS_DRV_INFO_REQ)
                bxe_handle_drv_info_req(sc);

            if ((sc->port.pmf == 0) && (val & DRV_STATUS_PMF))
                bxe_pmf_update(sc);

            if (val & DRV_STATUS_EEE_NEGOTIATION_RESULTS)
                bxe_handle_eee_event(sc);

            if (sc->link_vars.periodic_flags &
                ELINK_PERIODIC_FLAGS_LINK_EVENT) {
                /* sync with link */
		bxe_acquire_phy_lock(sc);
                sc->link_vars.periodic_flags &=
                    ~ELINK_PERIODIC_FLAGS_LINK_EVENT;
		bxe_release_phy_lock(sc);
                if (IS_MF(sc))
                    ; // XXX bxe_link_sync_notify(sc);
                bxe_link_report(sc);
            }

            /*
             * Always call it here: bxe_link_report() will
             * prevent the link indication duplication.
             */
            bxe_link_status_update(sc);

        } else if (attn & BXE_MC_ASSERT_BITS) {

            BLOGE(sc, "MC assert!\n");
            bxe_mc_assert(sc);
            REG_WR(sc, MISC_REG_AEU_GENERAL_ATTN_10, 0);
            REG_WR(sc, MISC_REG_AEU_GENERAL_ATTN_9, 0);
            REG_WR(sc, MISC_REG_AEU_GENERAL_ATTN_8, 0);
            REG_WR(sc, MISC_REG_AEU_GENERAL_ATTN_7, 0);
            bxe_int_disable(sc);
            BXE_SET_ERROR_BIT(sc, BXE_ERR_MC_ASSERT);
            taskqueue_enqueue_timeout(taskqueue_thread,
                &sc->sp_err_timeout_task, hz/10);
	
        } else if (attn & BXE_MCP_ASSERT) {

            BLOGE(sc, "MCP assert!\n");
            REG_WR(sc, MISC_REG_AEU_GENERAL_ATTN_11, 0);
            BXE_SET_ERROR_BIT(sc, BXE_ERR_MCP_ASSERT);
            taskqueue_enqueue_timeout(taskqueue_thread,
                &sc->sp_err_timeout_task, hz/10);
            bxe_int_disable(sc);  /*avoid repetive assert alert */


        } else {
            BLOGE(sc, "Unknown HW assert! (attn 0x%08x)\n", attn);
        }
    }

    if (attn & EVEREST_LATCHED_ATTN_IN_USE_MASK) {
        BLOGE(sc, "LATCHED attention 0x%08x (masked)\n", attn);
        if (attn & BXE_GRC_TIMEOUT) {
            val = CHIP_IS_E1(sc) ? 0 : REG_RD(sc, MISC_REG_GRC_TIMEOUT_ATTN);
            BLOGE(sc, "GRC time-out 0x%08x\n", val);
        }
        if (attn & BXE_GRC_RSV) {
            val = CHIP_IS_E1(sc) ? 0 : REG_RD(sc, MISC_REG_GRC_RSV_ATTN);
            BLOGE(sc, "GRC reserved 0x%08x\n", val);
        }
        REG_WR(sc, MISC_REG_AEU_CLR_LATCH_SIGNAL, 0x7ff);
    }
}