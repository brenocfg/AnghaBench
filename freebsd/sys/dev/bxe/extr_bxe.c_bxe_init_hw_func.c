#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ecore_ilt {TYPE_4__* lines; TYPE_2__* clients; } ;
struct TYPE_6__ {scalar_t__ int_block; } ;
struct bxe_softc {scalar_t__ interrupt_mode; int dmae_ready; int igu_sb_cnt; int igu_base_sb; int igu_dsb_id; int /*<<< orphan*/  link_params; TYPE_1__ devinfo; TYPE_5__* context; struct ecore_ilt* ilt; } ;
struct TYPE_8__ {int /*<<< orphan*/  paddr; } ;
struct TYPE_10__ {int /*<<< orphan*/  size; TYPE_3__ vcxt_dma; int /*<<< orphan*/  vcxt; } ;
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  page_mapping; int /*<<< orphan*/  page; } ;
struct TYPE_7__ {int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTENTION_ID ; 
 scalar_t__ BAR_CSTRORM_INTMEM ; 
 scalar_t__ BAR_TSTRORM_INTMEM ; 
 scalar_t__ BAR_USTRORM_INTMEM ; 
 scalar_t__ BAR_XSTRORM_INTMEM ; 
 int /*<<< orphan*/  BLOCK_ATC ; 
 int /*<<< orphan*/  BLOCK_BRB1 ; 
 int /*<<< orphan*/  BLOCK_CCM ; 
 int /*<<< orphan*/  BLOCK_CDU ; 
 int /*<<< orphan*/  BLOCK_CFC ; 
 int /*<<< orphan*/  BLOCK_CSDM ; 
 int /*<<< orphan*/  BLOCK_CSEM ; 
 int /*<<< orphan*/  BLOCK_DMAE ; 
 int /*<<< orphan*/  BLOCK_DORQ ; 
 int /*<<< orphan*/  BLOCK_HC ; 
 int /*<<< orphan*/  BLOCK_IGU ; 
 int /*<<< orphan*/  BLOCK_MISC ; 
 int /*<<< orphan*/  BLOCK_MISC_AEU ; 
 int /*<<< orphan*/  BLOCK_NIG ; 
 int /*<<< orphan*/  BLOCK_PBF ; 
 int /*<<< orphan*/  BLOCK_PGLUE_B ; 
 int /*<<< orphan*/  BLOCK_PRS ; 
 int /*<<< orphan*/  BLOCK_PXP ; 
 int /*<<< orphan*/  BLOCK_PXP2 ; 
 int /*<<< orphan*/  BLOCK_QM ; 
 int /*<<< orphan*/  BLOCK_SRC ; 
 int /*<<< orphan*/  BLOCK_TCM ; 
 int /*<<< orphan*/  BLOCK_TM ; 
 int /*<<< orphan*/  BLOCK_TSDM ; 
 int /*<<< orphan*/  BLOCK_TSEM ; 
 int /*<<< orphan*/  BLOCK_UCM ; 
 int /*<<< orphan*/  BLOCK_UPB ; 
 int /*<<< orphan*/  BLOCK_USDM ; 
 int /*<<< orphan*/  BLOCK_USEM ; 
 int /*<<< orphan*/  BLOCK_XCM ; 
 int /*<<< orphan*/  BLOCK_XPB ; 
 int /*<<< orphan*/  BLOCK_XSDM ; 
 int /*<<< orphan*/  BLOCK_XSEM ; 
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int BXE_MAX_NUM_OF_VFS ; 
 int /*<<< orphan*/  BXE_SP_MAPPING (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int CFC_REG_WEAK_ENABLE_PF ; 
 scalar_t__ CHIP_INT_MODE_IS_BC (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E1H (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E1x (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_MODE_4_PORT (struct bxe_softc*) ; 
 int CSEM_REG_VFPF_ERR_NUM ; 
 int /*<<< orphan*/  CSTORM_ID ; 
 scalar_t__ CSTORM_RECORD_SLOW_PATH_OFFSET (int) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int E1HVN_MAX ; 
 int HC_CONFIG_0_REG_MSI_ATTN_EN_0 ; 
 int HC_REG_CONFIG_0 ; 
 int HC_REG_CONFIG_1 ; 
 int HC_REG_HC_PRTY_STS_CLR ; 
 int HC_REG_LEADING_EDGE_0 ; 
 int HC_REG_MAIN_MEMORY ; 
 int HC_REG_MAIN_MEMORY_SIZE ; 
 int HC_REG_TRAILING_EDGE_0 ; 
 int IGU_BC_BASE_DSB_PROD ; 
 int IGU_BC_DSB_NUM_SEGS ; 
 int IGU_BC_NDSB_NUM_SEGS ; 
 int /*<<< orphan*/  IGU_INT_NOP ; 
 int IGU_NORM_BASE_DSB_PROD ; 
 int IGU_NORM_DSB_NUM_SEGS ; 
 int IGU_NORM_NDSB_NUM_SEGS ; 
 int IGU_PF_CONF_FUNC_EN ; 
 int IGU_PF_CONF_SINGLE_ISR_EN ; 
 int IGU_REG_LEADING_EDGE_LATCH ; 
 int IGU_REG_PBA_STATUS_LSB ; 
 int IGU_REG_PBA_STATUS_MSB ; 
 int IGU_REG_PF_CONFIGURATION ; 
 int IGU_REG_PROD_CONS_MEMORY ; 
 int IGU_REG_SB_INT_BEFORE_MASK_LSB ; 
 int IGU_REG_SB_INT_BEFORE_MASK_MSB ; 
 int IGU_REG_SB_MASK_LSB ; 
 int IGU_REG_SB_MASK_MSB ; 
 int IGU_REG_TRAILING_EDGE_LATCH ; 
 size_t ILT_CLIENT_CDU ; 
 int /*<<< orphan*/  INITOP_SET ; 
 scalar_t__ INTR_MODE_MSIX ; 
 scalar_t__ INT_BLOCK_HC ; 
 scalar_t__ IS_MF (struct bxe_softc*) ; 
 int L2_ILT_LINES (struct bxe_softc*) ; 
 int MISC_REG_AEU_GENERAL_ATTN_12 ; 
 int NIG_REG_LLH0_FUNC_EN ; 
 int NIG_REG_LLH0_FUNC_VLAN_ID ; 
 int OVLAN (struct bxe_softc*) ; 
 int PBF_REG_DISABLE_PF ; 
 int PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER ; 
 int PGLUE_B_REG_WAS_ERROR_PF_7_0_CLR ; 
 int PHASE_PF0 ; 
 int PRS_REG_NIC_MODE ; 
 int QM_REG_PF_EN ; 
 int REG_RD (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 
 int /*<<< orphan*/  REG_WR8 (struct bxe_softc*,scalar_t__,int) ; 
 int SC_FUNC (struct bxe_softc*) ; 
 int SC_PORT (struct bxe_softc*) ; 
 int SC_VN (struct bxe_softc*) ; 
 int TSEM_REG_VFPF_ERR_NUM ; 
 int /*<<< orphan*/  TSTORM_ID ; 
 scalar_t__ TSTORM_RECORD_SLOW_PATH_OFFSET (int) ; 
 int USEM_REG_VFPF_ERR_NUM ; 
 int /*<<< orphan*/  USTORM_ID ; 
 scalar_t__ USTORM_RECORD_SLOW_PATH_OFFSET (int) ; 
 int XSEM_REG_VFPF_ERR_NUM ; 
 int /*<<< orphan*/  XSTORM_ID ; 
 scalar_t__ XSTORM_RECORD_SLOW_PATH_OFFSET (int) ; 
 int /*<<< orphan*/  bxe_ack_sb (struct bxe_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bxe_igu_clear_sb (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  bxe_iov_init_dq (struct bxe_softc*) ; 
 int bxe_pf_flr_clnup (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_read_dmae (struct bxe_softc*,int,int) ; 
 int /*<<< orphan*/  bxe_write_dmae (struct bxe_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ecore_ilt_init_op (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_init_block (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elink_phy_probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wb_data ; 

__attribute__((used)) static int
bxe_init_hw_func(struct bxe_softc *sc)
{
    int port = SC_PORT(sc);
    int func = SC_FUNC(sc);
    int init_phase = PHASE_PF0 + func;
    struct ecore_ilt *ilt = sc->ilt;
    uint16_t cdu_ilt_start;
    uint32_t addr, val;
    uint32_t main_mem_base, main_mem_size, main_mem_prty_clr;
    int i, main_mem_width, rc;

    BLOGD(sc, DBG_LOAD, "starting func init for func %d\n", func);

    /* FLR cleanup */
    if (!CHIP_IS_E1x(sc)) {
        rc = bxe_pf_flr_clnup(sc);
        if (rc) {
            BLOGE(sc, "FLR cleanup failed!\n");
            // XXX bxe_fw_dump(sc);
            // XXX bxe_idle_chk(sc);
            return (rc);
        }
    }

    /* set MSI reconfigure capability */
    if (sc->devinfo.int_block == INT_BLOCK_HC) {
        addr = (port ? HC_REG_CONFIG_1 : HC_REG_CONFIG_0);
        val = REG_RD(sc, addr);
        val |= HC_CONFIG_0_REG_MSI_ATTN_EN_0;
        REG_WR(sc, addr, val);
    }

    ecore_init_block(sc, BLOCK_PXP, init_phase);
    ecore_init_block(sc, BLOCK_PXP2, init_phase);

    ilt = sc->ilt;
    cdu_ilt_start = ilt->clients[ILT_CLIENT_CDU].start;

    for (i = 0; i < L2_ILT_LINES(sc); i++) {
        ilt->lines[cdu_ilt_start + i].page = sc->context[i].vcxt;
        ilt->lines[cdu_ilt_start + i].page_mapping =
            sc->context[i].vcxt_dma.paddr;
        ilt->lines[cdu_ilt_start + i].size = sc->context[i].size;
    }
    ecore_ilt_init_op(sc, INITOP_SET);

    /* Set NIC mode */
    REG_WR(sc, PRS_REG_NIC_MODE, 1);
    BLOGD(sc, DBG_LOAD, "NIC MODE configured\n");

    if (!CHIP_IS_E1x(sc)) {
        uint32_t pf_conf = IGU_PF_CONF_FUNC_EN;

        /* Turn on a single ISR mode in IGU if driver is going to use
         * INT#x or MSI
         */
        if (sc->interrupt_mode != INTR_MODE_MSIX) {
            pf_conf |= IGU_PF_CONF_SINGLE_ISR_EN;
        }

        /*
         * Timers workaround bug: function init part.
         * Need to wait 20msec after initializing ILT,
         * needed to make sure there are no requests in
         * one of the PXP internal queues with "old" ILT addresses
         */
        DELAY(20000);

        /*
         * Master enable - Due to WB DMAE writes performed before this
         * register is re-initialized as part of the regular function
         * init
         */
        REG_WR(sc, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 1);
        /* Enable the function in IGU */
        REG_WR(sc, IGU_REG_PF_CONFIGURATION, pf_conf);
    }

    sc->dmae_ready = 1;

    ecore_init_block(sc, BLOCK_PGLUE_B, init_phase);

    if (!CHIP_IS_E1x(sc))
        REG_WR(sc, PGLUE_B_REG_WAS_ERROR_PF_7_0_CLR, func);

    ecore_init_block(sc, BLOCK_ATC, init_phase);
    ecore_init_block(sc, BLOCK_DMAE, init_phase);
    ecore_init_block(sc, BLOCK_NIG, init_phase);
    ecore_init_block(sc, BLOCK_SRC, init_phase);
    ecore_init_block(sc, BLOCK_MISC, init_phase);
    ecore_init_block(sc, BLOCK_TCM, init_phase);
    ecore_init_block(sc, BLOCK_UCM, init_phase);
    ecore_init_block(sc, BLOCK_CCM, init_phase);
    ecore_init_block(sc, BLOCK_XCM, init_phase);
    ecore_init_block(sc, BLOCK_TSEM, init_phase);
    ecore_init_block(sc, BLOCK_USEM, init_phase);
    ecore_init_block(sc, BLOCK_CSEM, init_phase);
    ecore_init_block(sc, BLOCK_XSEM, init_phase);

    if (!CHIP_IS_E1x(sc))
        REG_WR(sc, QM_REG_PF_EN, 1);

    if (!CHIP_IS_E1x(sc)) {
        REG_WR(sc, TSEM_REG_VFPF_ERR_NUM, BXE_MAX_NUM_OF_VFS + func);
        REG_WR(sc, USEM_REG_VFPF_ERR_NUM, BXE_MAX_NUM_OF_VFS + func);
        REG_WR(sc, CSEM_REG_VFPF_ERR_NUM, BXE_MAX_NUM_OF_VFS + func);
        REG_WR(sc, XSEM_REG_VFPF_ERR_NUM, BXE_MAX_NUM_OF_VFS + func);
    }
    ecore_init_block(sc, BLOCK_QM, init_phase);

    ecore_init_block(sc, BLOCK_TM, init_phase);
    ecore_init_block(sc, BLOCK_DORQ, init_phase);

    bxe_iov_init_dq(sc);

    ecore_init_block(sc, BLOCK_BRB1, init_phase);
    ecore_init_block(sc, BLOCK_PRS, init_phase);
    ecore_init_block(sc, BLOCK_TSDM, init_phase);
    ecore_init_block(sc, BLOCK_CSDM, init_phase);
    ecore_init_block(sc, BLOCK_USDM, init_phase);
    ecore_init_block(sc, BLOCK_XSDM, init_phase);
    ecore_init_block(sc, BLOCK_UPB, init_phase);
    ecore_init_block(sc, BLOCK_XPB, init_phase);
    ecore_init_block(sc, BLOCK_PBF, init_phase);
    if (!CHIP_IS_E1x(sc))
        REG_WR(sc, PBF_REG_DISABLE_PF, 0);

    ecore_init_block(sc, BLOCK_CDU, init_phase);

    ecore_init_block(sc, BLOCK_CFC, init_phase);

    if (!CHIP_IS_E1x(sc))
        REG_WR(sc, CFC_REG_WEAK_ENABLE_PF, 1);

    if (IS_MF(sc)) {
        REG_WR(sc, NIG_REG_LLH0_FUNC_EN + port*8, 1);
        REG_WR(sc, NIG_REG_LLH0_FUNC_VLAN_ID + port*8, OVLAN(sc));
    }

    ecore_init_block(sc, BLOCK_MISC_AEU, init_phase);

    /* HC init per function */
    if (sc->devinfo.int_block == INT_BLOCK_HC) {
        if (CHIP_IS_E1H(sc)) {
            REG_WR(sc, MISC_REG_AEU_GENERAL_ATTN_12 + func*4, 0);

            REG_WR(sc, HC_REG_LEADING_EDGE_0 + port*8, 0);
            REG_WR(sc, HC_REG_TRAILING_EDGE_0 + port*8, 0);
        }
        ecore_init_block(sc, BLOCK_HC, init_phase);

    } else {
        int num_segs, sb_idx, prod_offset;

        REG_WR(sc, MISC_REG_AEU_GENERAL_ATTN_12 + func*4, 0);

        if (!CHIP_IS_E1x(sc)) {
            REG_WR(sc, IGU_REG_LEADING_EDGE_LATCH, 0);
            REG_WR(sc, IGU_REG_TRAILING_EDGE_LATCH, 0);
        }

        ecore_init_block(sc, BLOCK_IGU, init_phase);

        if (!CHIP_IS_E1x(sc)) {
            int dsb_idx = 0;
            /**
             * Producer memory:
             * E2 mode: address 0-135 match to the mapping memory;
             * 136 - PF0 default prod; 137 - PF1 default prod;
             * 138 - PF2 default prod; 139 - PF3 default prod;
             * 140 - PF0 attn prod;    141 - PF1 attn prod;
             * 142 - PF2 attn prod;    143 - PF3 attn prod;
             * 144-147 reserved.
             *
             * E1.5 mode - In backward compatible mode;
             * for non default SB; each even line in the memory
             * holds the U producer and each odd line hold
             * the C producer. The first 128 producers are for
             * NDSB (PF0 - 0-31; PF1 - 32-63 and so on). The last 20
             * producers are for the DSB for each PF.
             * Each PF has five segments: (the order inside each
             * segment is PF0; PF1; PF2; PF3) - 128-131 U prods;
             * 132-135 C prods; 136-139 X prods; 140-143 T prods;
             * 144-147 attn prods;
             */
            /* non-default-status-blocks */
            num_segs = CHIP_INT_MODE_IS_BC(sc) ?
                IGU_BC_NDSB_NUM_SEGS : IGU_NORM_NDSB_NUM_SEGS;
            for (sb_idx = 0; sb_idx < sc->igu_sb_cnt; sb_idx++) {
                prod_offset = (sc->igu_base_sb + sb_idx) *
                    num_segs;

                for (i = 0; i < num_segs; i++) {
                    addr = IGU_REG_PROD_CONS_MEMORY +
                            (prod_offset + i) * 4;
                    REG_WR(sc, addr, 0);
                }
                /* send consumer update with value 0 */
                bxe_ack_sb(sc, sc->igu_base_sb + sb_idx,
                           USTORM_ID, 0, IGU_INT_NOP, 1);
                bxe_igu_clear_sb(sc, sc->igu_base_sb + sb_idx);
            }

            /* default-status-blocks */
            num_segs = CHIP_INT_MODE_IS_BC(sc) ?
                IGU_BC_DSB_NUM_SEGS : IGU_NORM_DSB_NUM_SEGS;

            if (CHIP_IS_MODE_4_PORT(sc))
                dsb_idx = SC_FUNC(sc);
            else
                dsb_idx = SC_VN(sc);

            prod_offset = (CHIP_INT_MODE_IS_BC(sc) ?
                       IGU_BC_BASE_DSB_PROD + dsb_idx :
                       IGU_NORM_BASE_DSB_PROD + dsb_idx);

            /*
             * igu prods come in chunks of E1HVN_MAX (4) -
             * does not matters what is the current chip mode
             */
            for (i = 0; i < (num_segs * E1HVN_MAX);
                 i += E1HVN_MAX) {
                addr = IGU_REG_PROD_CONS_MEMORY +
                            (prod_offset + i)*4;
                REG_WR(sc, addr, 0);
            }
            /* send consumer update with 0 */
            if (CHIP_INT_MODE_IS_BC(sc)) {
                bxe_ack_sb(sc, sc->igu_dsb_id,
                           USTORM_ID, 0, IGU_INT_NOP, 1);
                bxe_ack_sb(sc, sc->igu_dsb_id,
                           CSTORM_ID, 0, IGU_INT_NOP, 1);
                bxe_ack_sb(sc, sc->igu_dsb_id,
                           XSTORM_ID, 0, IGU_INT_NOP, 1);
                bxe_ack_sb(sc, sc->igu_dsb_id,
                           TSTORM_ID, 0, IGU_INT_NOP, 1);
                bxe_ack_sb(sc, sc->igu_dsb_id,
                           ATTENTION_ID, 0, IGU_INT_NOP, 1);
            } else {
                bxe_ack_sb(sc, sc->igu_dsb_id,
                           USTORM_ID, 0, IGU_INT_NOP, 1);
                bxe_ack_sb(sc, sc->igu_dsb_id,
                           ATTENTION_ID, 0, IGU_INT_NOP, 1);
            }
            bxe_igu_clear_sb(sc, sc->igu_dsb_id);

            /* !!! these should become driver const once
               rf-tool supports split-68 const */
            REG_WR(sc, IGU_REG_SB_INT_BEFORE_MASK_LSB, 0);
            REG_WR(sc, IGU_REG_SB_INT_BEFORE_MASK_MSB, 0);
            REG_WR(sc, IGU_REG_SB_MASK_LSB, 0);
            REG_WR(sc, IGU_REG_SB_MASK_MSB, 0);
            REG_WR(sc, IGU_REG_PBA_STATUS_LSB, 0);
            REG_WR(sc, IGU_REG_PBA_STATUS_MSB, 0);
        }
    }

    /* Reset PCIE errors for debug */
    REG_WR(sc, 0x2114, 0xffffffff);
    REG_WR(sc, 0x2120, 0xffffffff);

    if (CHIP_IS_E1x(sc)) {
        main_mem_size = HC_REG_MAIN_MEMORY_SIZE / 2; /*dwords*/
        main_mem_base = HC_REG_MAIN_MEMORY +
                SC_PORT(sc) * (main_mem_size * 4);
        main_mem_prty_clr = HC_REG_HC_PRTY_STS_CLR;
        main_mem_width = 8;

        val = REG_RD(sc, main_mem_prty_clr);
        if (val) {
            BLOGD(sc, DBG_LOAD,
                  "Parity errors in HC block during function init (0x%x)!\n",
                  val);
        }

        /* Clear "false" parity errors in MSI-X table */
        for (i = main_mem_base;
             i < main_mem_base + main_mem_size * 4;
             i += main_mem_width) {
            bxe_read_dmae(sc, i, main_mem_width / 4);
            bxe_write_dmae(sc, BXE_SP_MAPPING(sc, wb_data),
                           i, main_mem_width / 4);
        }
        /* Clear HC parity attention */
        REG_RD(sc, main_mem_prty_clr);
    }

#if 1
    /* Enable STORMs SP logging */
    REG_WR8(sc, BAR_USTRORM_INTMEM +
           USTORM_RECORD_SLOW_PATH_OFFSET(SC_FUNC(sc)), 1);
    REG_WR8(sc, BAR_TSTRORM_INTMEM +
           TSTORM_RECORD_SLOW_PATH_OFFSET(SC_FUNC(sc)), 1);
    REG_WR8(sc, BAR_CSTRORM_INTMEM +
           CSTORM_RECORD_SLOW_PATH_OFFSET(SC_FUNC(sc)), 1);
    REG_WR8(sc, BAR_XSTRORM_INTMEM +
           XSTORM_RECORD_SLOW_PATH_OFFSET(SC_FUNC(sc)), 1);
#endif

    elink_phy_probe(&sc->link_params);

    return (0);
}