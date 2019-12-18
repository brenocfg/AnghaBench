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
typedef  union cdu_context {int dummy; } cdu_context ;
typedef  int uint8_t ;
typedef  int uint32_t ;
struct ilt_client_info {int /*<<< orphan*/  client_num; scalar_t__ end; scalar_t__ start; } ;
struct ecore_ilt {int /*<<< orphan*/  client_num; scalar_t__ end; scalar_t__ start; } ;
struct TYPE_3__ {int path_has_ovlan; } ;
struct TYPE_4__ {TYPE_1__ mf_info; } ;
struct bxe_softc {int dmae_ready; TYPE_2__ devinfo; int /*<<< orphan*/  qm_cid_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATC_REG_ATC_INIT_DONE ; 
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
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int) ; 
 int BXE_DB_SHIFT ; 
 scalar_t__ BXE_NOMCP (struct bxe_softc*) ; 
 int BXE_PXP_DRAM_ALIGN ; 
 int* BXE_SP (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int CDU_REG_CDU_GLOBAL_PARAMS ; 
 int /*<<< orphan*/  CFC_REG_AC_INIT_DONE ; 
 int /*<<< orphan*/  CFC_REG_CAM_INIT_DONE ; 
 int CFC_REG_CFC_INT_MASK ; 
 int CFC_REG_DEBUG0 ; 
 int CFC_REG_INIT_REG ; 
 int /*<<< orphan*/  CFC_REG_LL_INIT_DONE ; 
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E1H (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E1x (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  CHIP_IS_E3B0 (struct bxe_softc*) ; 
 scalar_t__ CHIP_REV_IS_EMUL (struct bxe_softc*) ; 
 scalar_t__ CHIP_REV_IS_FPGA (struct bxe_softc*) ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bxe_softc*) ; 
 scalar_t__ CNIC_SUPPORT (struct bxe_softc*) ; 
 int /*<<< orphan*/  CSEM_REG_PASSIVE_BUFFER ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int DORQ_REG_DORQ_INT_MASK ; 
 int DORQ_REG_DPM_CID_OFST ; 
 int E2_FUNC_MAX ; 
 int GRCBASE_MISC ; 
 int /*<<< orphan*/  HW_LOCK_RESOURCE_RESET ; 
 int IGU_REG_RESET_MEMORIES ; 
 int /*<<< orphan*/  ILT_CLIENT_TM ; 
 scalar_t__ ILT_NUM_PAGE_ENTRIES ; 
 int /*<<< orphan*/  INITOP_CLEAR ; 
 int /*<<< orphan*/  INITOP_SET ; 
 int IS_MF (struct bxe_softc*) ; 
 scalar_t__ IS_MF_AFEX (struct bxe_softc*) ; 
 int IS_MF_SD (struct bxe_softc*) ; 
 int MISC_REGISTERS_RESET_REG_1_CLEAR ; 
 int MISC_REGISTERS_RESET_REG_1_SET ; 
 int MISC_REGISTERS_RESET_REG_2_MSTAT0 ; 
 int MISC_REGISTERS_RESET_REG_2_MSTAT1 ; 
 int MISC_REGISTERS_RESET_REG_2_SET ; 
 int NIG_REG_LLH_E1HOV_MODE ; 
 int NIG_REG_LLH_MF_MODE ; 
 int /*<<< orphan*/  NIG_REG_STAT2_BRB_OCTET ; 
 int PBF_REG_HDRS_AFTER_BASIC ; 
 int PBF_REG_HDRS_AFTER_TAG_0 ; 
 int PBF_REG_MUST_HAVE_HDRS ; 
 int PBF_REG_TAG_ETHERTYPE_0 ; 
 int PBF_REG_TAG_LEN_0 ; 
 int PCICFG_OFFSET ; 
 int PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER ; 
 int /*<<< orphan*/  PHASE_COMMON ; 
 int PRS_REG_A_PRSU_20 ; 
 int PRS_REG_E1HOV_MODE ; 
 int PRS_REG_HDRS_AFTER_BASIC ; 
 int PRS_REG_HDRS_AFTER_TAG_0 ; 
 int PRS_REG_MUST_HAVE_HDRS ; 
 int PRS_REG_TAG_ETHERTYPE_0 ; 
 int PRS_REG_TAG_LEN_0 ; 
 int PXP2_REG_PGL_TAGS_LIMIT ; 
 int /*<<< orphan*/  PXP2_REG_PXP2_INT_STS_CLR_0 ; 
 int PXP2_REG_RD_CDURD_SWAP_MODE ; 
 int PXP2_REG_RD_DISABLE_INPUTS ; 
 int /*<<< orphan*/  PXP2_REG_RD_INIT_DONE ; 
 int PXP2_REG_RD_QM_SWAP_MODE ; 
 int PXP2_REG_RD_SRC_SWAP_MODE ; 
 int PXP2_REG_RD_TM_SWAP_MODE ; 
 int PXP2_REG_RQ_CDU_ENDIAN_M ; 
 int /*<<< orphan*/  PXP2_REG_RQ_CFG_DONE ; 
 int PXP2_REG_RQ_DBG_ENDIAN_M ; 
 int PXP2_REG_RQ_DISABLE_INPUTS ; 
 int PXP2_REG_RQ_DRAM_ALIGN ; 
 int PXP2_REG_RQ_DRAM_ALIGN_RD ; 
 int PXP2_REG_RQ_DRAM_ALIGN_SEL ; 
 int PXP2_REG_RQ_HC_ENDIAN_M ; 
 int PXP2_REG_RQ_QM_ENDIAN_M ; 
 int PXP2_REG_RQ_SRC_ENDIAN_M ; 
 int PXP2_REG_RQ_TM_ENDIAN_M ; 
 int PXPCS_TL_CONTROL_5 ; 
 int PXPCS_TL_CONTROL_5_ERR_UNSPPORT ; 
 int PXPCS_TL_CONTROL_5_ERR_UNSPPORT1 ; 
 int PXPCS_TL_FUNC345_STAT ; 
 int PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT2 ; 
 int PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT3 ; 
 int PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT4 ; 
 int PXPCS_TL_FUNC678_STAT ; 
 int PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT5 ; 
 int PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT6 ; 
 int PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT7 ; 
 int PXP_REG_PXP_INT_MASK_0 ; 
 int QM_REG_SOFT_RESET ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 
 int SC_ABS_FUNC (struct bxe_softc*) ; 
 int SC_PATH (struct bxe_softc*) ; 
 int SRC_REG_KEYSEARCH_0 ; 
 int SRC_REG_KEYSEARCH_1 ; 
 int SRC_REG_KEYSEARCH_2 ; 
 int SRC_REG_KEYSEARCH_3 ; 
 int SRC_REG_KEYSEARCH_4 ; 
 int SRC_REG_KEYSEARCH_5 ; 
 int SRC_REG_KEYSEARCH_6 ; 
 int SRC_REG_KEYSEARCH_7 ; 
 int SRC_REG_KEYSEARCH_8 ; 
 int SRC_REG_KEYSEARCH_9 ; 
 int SRC_REG_SOFT_RST ; 
 int TSEM_REG_FAST_MEMORY ; 
 int /*<<< orphan*/  TSEM_REG_PASSIVE_BUFFER ; 
 int /*<<< orphan*/  TSEM_REG_PRAM ; 
 int /*<<< orphan*/  USEM_REG_PASSIVE_BUFFER ; 
 int VFC_MEMORIES_RST_REG_CAM_RST ; 
 int VFC_MEMORIES_RST_REG_RAM_RST ; 
 int VFC_REG_MEMORIES_RST ; 
 int XSEM_REG_FAST_MEMORY ; 
 int /*<<< orphan*/  XSEM_REG_PASSIVE_BUFFER ; 
 int /*<<< orphan*/  bxe_acquire_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_common_init_phy (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_enable_blocks_attention (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_init_pxp (struct bxe_softc*) ; 
 scalar_t__ bxe_int_mem_test (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_iov_init_dmae (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_pf_disable (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_pretend_func (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  bxe_read_dmae (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bxe_release_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_reset_common (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_setup_fan_failure_detection (struct bxe_softc*) ; 
 int /*<<< orphan*/  ecore_enable_blocks_parity (struct bxe_softc*) ; 
 int /*<<< orphan*/  ecore_ilt_client_init_op_ilt (struct bxe_softc*,struct ilt_client_info*,struct ilt_client_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_ilt_init_page_size (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_init_block (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_init_fill (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ecore_qm_init_ptr_table (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ilt_client_info*,int /*<<< orphan*/ ,int) ; 
 int reg_poll (struct bxe_softc*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * wb_data ; 

__attribute__((used)) static int
bxe_init_hw_common(struct bxe_softc *sc)
{
    uint8_t abs_func_id;
    uint32_t val;

    BLOGD(sc, DBG_LOAD, "starting common init for func %d\n",
          SC_ABS_FUNC(sc));

    /*
     * take the RESET lock to protect undi_unload flow from accessing
     * registers while we are resetting the chip
     */
    bxe_acquire_hw_lock(sc, HW_LOCK_RESOURCE_RESET);

    bxe_reset_common(sc);

    REG_WR(sc, (GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_SET), 0xffffffff);

    val = 0xfffc;
    if (CHIP_IS_E3(sc)) {
        val |= MISC_REGISTERS_RESET_REG_2_MSTAT0;
        val |= MISC_REGISTERS_RESET_REG_2_MSTAT1;
    }

    REG_WR(sc, (GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET), val);

    bxe_release_hw_lock(sc, HW_LOCK_RESOURCE_RESET);

    ecore_init_block(sc, BLOCK_MISC, PHASE_COMMON);
    BLOGD(sc, DBG_LOAD, "after misc block init\n");

    if (!CHIP_IS_E1x(sc)) {
        /*
         * 4-port mode or 2-port mode we need to turn off master-enable for
         * everyone. After that we turn it back on for self. So, we disregard
         * multi-function, and always disable all functions on the given path,
         * this means 0,2,4,6 for path 0 and 1,3,5,7 for path 1
         */
        for (abs_func_id = SC_PATH(sc);
             abs_func_id < (E2_FUNC_MAX * 2);
             abs_func_id += 2) {
            if (abs_func_id == SC_ABS_FUNC(sc)) {
                REG_WR(sc, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 1);
                continue;
            }

            bxe_pretend_func(sc, abs_func_id);

            /* clear pf enable */
            bxe_pf_disable(sc);

            bxe_pretend_func(sc, SC_ABS_FUNC(sc));
        }
    }

    BLOGD(sc, DBG_LOAD, "after pf disable\n");

    ecore_init_block(sc, BLOCK_PXP, PHASE_COMMON);

    if (CHIP_IS_E1(sc)) {
        /*
         * enable HW interrupt from PXP on USDM overflow
         * bit 16 on INT_MASK_0
         */
        REG_WR(sc, PXP_REG_PXP_INT_MASK_0, 0);
    }

    ecore_init_block(sc, BLOCK_PXP2, PHASE_COMMON);
    bxe_init_pxp(sc);

#ifdef __BIG_ENDIAN
    REG_WR(sc, PXP2_REG_RQ_QM_ENDIAN_M, 1);
    REG_WR(sc, PXP2_REG_RQ_TM_ENDIAN_M, 1);
    REG_WR(sc, PXP2_REG_RQ_SRC_ENDIAN_M, 1);
    REG_WR(sc, PXP2_REG_RQ_CDU_ENDIAN_M, 1);
    REG_WR(sc, PXP2_REG_RQ_DBG_ENDIAN_M, 1);
    /* make sure this value is 0 */
    REG_WR(sc, PXP2_REG_RQ_HC_ENDIAN_M, 0);

    //REG_WR(sc, PXP2_REG_RD_PBF_SWAP_MODE, 1);
    REG_WR(sc, PXP2_REG_RD_QM_SWAP_MODE, 1);
    REG_WR(sc, PXP2_REG_RD_TM_SWAP_MODE, 1);
    REG_WR(sc, PXP2_REG_RD_SRC_SWAP_MODE, 1);
    REG_WR(sc, PXP2_REG_RD_CDURD_SWAP_MODE, 1);
#endif

    ecore_ilt_init_page_size(sc, INITOP_SET);

    if (CHIP_REV_IS_FPGA(sc) && CHIP_IS_E1H(sc)) {
        REG_WR(sc, PXP2_REG_PGL_TAGS_LIMIT, 0x1);
    }

    /* let the HW do it's magic... */
    DELAY(100000);

    /* finish PXP init */
    val = REG_RD(sc, PXP2_REG_RQ_CFG_DONE);
    if (val != 1) {
        BLOGE(sc, "PXP2 CFG failed PXP2_REG_RQ_CFG_DONE val = 0x%x\n",
            val);
        return (-1);
    }
    val = REG_RD(sc, PXP2_REG_RD_INIT_DONE);
    if (val != 1) {
        BLOGE(sc, "PXP2 RD_INIT failed val = 0x%x\n", val);
        return (-1);
    }

    BLOGD(sc, DBG_LOAD, "after pxp init\n");

    /*
     * Timer bug workaround for E2 only. We need to set the entire ILT to have
     * entries with value "0" and valid bit on. This needs to be done by the
     * first PF that is loaded in a path (i.e. common phase)
     */
    if (!CHIP_IS_E1x(sc)) {
/*
 * In E2 there is a bug in the timers block that can cause function 6 / 7
 * (i.e. vnic3) to start even if it is marked as "scan-off".
 * This occurs when a different function (func2,3) is being marked
 * as "scan-off". Real-life scenario for example: if a driver is being
 * load-unloaded while func6,7 are down. This will cause the timer to access
 * the ilt, translate to a logical address and send a request to read/write.
 * Since the ilt for the function that is down is not valid, this will cause
 * a translation error which is unrecoverable.
 * The Workaround is intended to make sure that when this happens nothing
 * fatal will occur. The workaround:
 *  1.  First PF driver which loads on a path will:
 *      a.  After taking the chip out of reset, by using pretend,
 *          it will write "0" to the following registers of
 *          the other vnics.
 *          REG_WR(pdev, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 0);
 *          REG_WR(pdev, CFC_REG_WEAK_ENABLE_PF,0);
 *          REG_WR(pdev, CFC_REG_STRONG_ENABLE_PF,0);
 *          And for itself it will write '1' to
 *          PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER to enable
 *          dmae-operations (writing to pram for example.)
 *          note: can be done for only function 6,7 but cleaner this
 *            way.
 *      b.  Write zero+valid to the entire ILT.
 *      c.  Init the first_timers_ilt_entry, last_timers_ilt_entry of
 *          VNIC3 (of that port). The range allocated will be the
 *          entire ILT. This is needed to prevent  ILT range error.
 *  2.  Any PF driver load flow:
 *      a.  ILT update with the physical addresses of the allocated
 *          logical pages.
 *      b.  Wait 20msec. - note that this timeout is needed to make
 *          sure there are no requests in one of the PXP internal
 *          queues with "old" ILT addresses.
 *      c.  PF enable in the PGLC.
 *      d.  Clear the was_error of the PF in the PGLC. (could have
 *          occurred while driver was down)
 *      e.  PF enable in the CFC (WEAK + STRONG)
 *      f.  Timers scan enable
 *  3.  PF driver unload flow:
 *      a.  Clear the Timers scan_en.
 *      b.  Polling for scan_on=0 for that PF.
 *      c.  Clear the PF enable bit in the PXP.
 *      d.  Clear the PF enable in the CFC (WEAK + STRONG)
 *      e.  Write zero+valid to all ILT entries (The valid bit must
 *          stay set)
 *      f.  If this is VNIC 3 of a port then also init
 *          first_timers_ilt_entry to zero and last_timers_ilt_entry
 *          to the last enrty in the ILT.
 *
 *      Notes:
 *      Currently the PF error in the PGLC is non recoverable.
 *      In the future the there will be a recovery routine for this error.
 *      Currently attention is masked.
 *      Having an MCP lock on the load/unload process does not guarantee that
 *      there is no Timer disable during Func6/7 enable. This is because the
 *      Timers scan is currently being cleared by the MCP on FLR.
 *      Step 2.d can be done only for PF6/7 and the driver can also check if
 *      there is error before clearing it. But the flow above is simpler and
 *      more general.
 *      All ILT entries are written by zero+valid and not just PF6/7
 *      ILT entries since in the future the ILT entries allocation for
 *      PF-s might be dynamic.
 */
        struct ilt_client_info ilt_cli;
        struct ecore_ilt ilt;

        memset(&ilt_cli, 0, sizeof(struct ilt_client_info));
        memset(&ilt, 0, sizeof(struct ecore_ilt));

        /* initialize dummy TM client */
        ilt_cli.start      = 0;
        ilt_cli.end        = ILT_NUM_PAGE_ENTRIES - 1;
        ilt_cli.client_num = ILT_CLIENT_TM;

        /*
         * Step 1: set zeroes to all ilt page entries with valid bit on
         * Step 2: set the timers first/last ilt entry to point
         * to the entire range to prevent ILT range error for 3rd/4th
         * vnic (this code assumes existence of the vnic)
         *
         * both steps performed by call to ecore_ilt_client_init_op()
         * with dummy TM client
         *
         * we must use pretend since PXP2_REG_RQ_##blk##_FIRST_ILT
         * and his brother are split registers
         */

        bxe_pretend_func(sc, (SC_PATH(sc) + 6));
        ecore_ilt_client_init_op_ilt(sc, &ilt, &ilt_cli, INITOP_CLEAR);
        bxe_pretend_func(sc, SC_ABS_FUNC(sc));

        REG_WR(sc, PXP2_REG_RQ_DRAM_ALIGN, BXE_PXP_DRAM_ALIGN);
        REG_WR(sc, PXP2_REG_RQ_DRAM_ALIGN_RD, BXE_PXP_DRAM_ALIGN);
        REG_WR(sc, PXP2_REG_RQ_DRAM_ALIGN_SEL, 1);
    }

    REG_WR(sc, PXP2_REG_RQ_DISABLE_INPUTS, 0);
    REG_WR(sc, PXP2_REG_RD_DISABLE_INPUTS, 0);

    if (!CHIP_IS_E1x(sc)) {
        int factor = CHIP_REV_IS_EMUL(sc) ? 1000 :
                     (CHIP_REV_IS_FPGA(sc) ? 400 : 0);

        ecore_init_block(sc, BLOCK_PGLUE_B, PHASE_COMMON);
        ecore_init_block(sc, BLOCK_ATC, PHASE_COMMON);

        /* let the HW do it's magic... */
        do {
            DELAY(200000);
            val = REG_RD(sc, ATC_REG_ATC_INIT_DONE);
        } while (factor-- && (val != 1));

        if (val != 1) {
            BLOGE(sc, "ATC_INIT failed val = 0x%x\n", val);
            return (-1);
        }
    }

    BLOGD(sc, DBG_LOAD, "after pglue and atc init\n");

    ecore_init_block(sc, BLOCK_DMAE, PHASE_COMMON);

    bxe_iov_init_dmae(sc);

    /* clean the DMAE memory */
    sc->dmae_ready = 1;
    ecore_init_fill(sc, TSEM_REG_PRAM, 0, 8, 1);

    ecore_init_block(sc, BLOCK_TCM, PHASE_COMMON);

    ecore_init_block(sc, BLOCK_UCM, PHASE_COMMON);

    ecore_init_block(sc, BLOCK_CCM, PHASE_COMMON);

    ecore_init_block(sc, BLOCK_XCM, PHASE_COMMON);

    bxe_read_dmae(sc, XSEM_REG_PASSIVE_BUFFER, 3);
    bxe_read_dmae(sc, CSEM_REG_PASSIVE_BUFFER, 3);
    bxe_read_dmae(sc, TSEM_REG_PASSIVE_BUFFER, 3);
    bxe_read_dmae(sc, USEM_REG_PASSIVE_BUFFER, 3);

    ecore_init_block(sc, BLOCK_QM, PHASE_COMMON);

    /* QM queues pointers table */
    ecore_qm_init_ptr_table(sc, sc->qm_cid_count, INITOP_SET);

    /* soft reset pulse */
    REG_WR(sc, QM_REG_SOFT_RESET, 1);
    REG_WR(sc, QM_REG_SOFT_RESET, 0);

    if (CNIC_SUPPORT(sc))
        ecore_init_block(sc, BLOCK_TM, PHASE_COMMON);

    ecore_init_block(sc, BLOCK_DORQ, PHASE_COMMON);
    REG_WR(sc, DORQ_REG_DPM_CID_OFST, BXE_DB_SHIFT);
    if (!CHIP_REV_IS_SLOW(sc)) {
        /* enable hw interrupt from doorbell Q */
        REG_WR(sc, DORQ_REG_DORQ_INT_MASK, 0);
    }

    ecore_init_block(sc, BLOCK_BRB1, PHASE_COMMON);

    ecore_init_block(sc, BLOCK_PRS, PHASE_COMMON);
    REG_WR(sc, PRS_REG_A_PRSU_20, 0xf);

    if (!CHIP_IS_E1(sc)) {
        REG_WR(sc, PRS_REG_E1HOV_MODE, sc->devinfo.mf_info.path_has_ovlan);
    }

    if (!CHIP_IS_E1x(sc) && !CHIP_IS_E3B0(sc)) {
        if (IS_MF_AFEX(sc)) {
            /*
             * configure that AFEX and VLAN headers must be
             * received in AFEX mode
             */
            REG_WR(sc, PRS_REG_HDRS_AFTER_BASIC, 0xE);
            REG_WR(sc, PRS_REG_MUST_HAVE_HDRS, 0xA);
            REG_WR(sc, PRS_REG_HDRS_AFTER_TAG_0, 0x6);
            REG_WR(sc, PRS_REG_TAG_ETHERTYPE_0, 0x8926);
            REG_WR(sc, PRS_REG_TAG_LEN_0, 0x4);
        } else {
            /*
             * Bit-map indicating which L2 hdrs may appear
             * after the basic Ethernet header
             */
            REG_WR(sc, PRS_REG_HDRS_AFTER_BASIC,
                   sc->devinfo.mf_info.path_has_ovlan ? 7 : 6);
        }
    }

    ecore_init_block(sc, BLOCK_TSDM, PHASE_COMMON);
    ecore_init_block(sc, BLOCK_CSDM, PHASE_COMMON);
    ecore_init_block(sc, BLOCK_USDM, PHASE_COMMON);
    ecore_init_block(sc, BLOCK_XSDM, PHASE_COMMON);

    if (!CHIP_IS_E1x(sc)) {
        /* reset VFC memories */
        REG_WR(sc, TSEM_REG_FAST_MEMORY + VFC_REG_MEMORIES_RST,
               VFC_MEMORIES_RST_REG_CAM_RST |
               VFC_MEMORIES_RST_REG_RAM_RST);
        REG_WR(sc, XSEM_REG_FAST_MEMORY + VFC_REG_MEMORIES_RST,
               VFC_MEMORIES_RST_REG_CAM_RST |
               VFC_MEMORIES_RST_REG_RAM_RST);

        DELAY(20000);
    }

    ecore_init_block(sc, BLOCK_TSEM, PHASE_COMMON);
    ecore_init_block(sc, BLOCK_USEM, PHASE_COMMON);
    ecore_init_block(sc, BLOCK_CSEM, PHASE_COMMON);
    ecore_init_block(sc, BLOCK_XSEM, PHASE_COMMON);

    /* sync semi rtc */
    REG_WR(sc, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_CLEAR,
           0x80000000);
    REG_WR(sc, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_SET,
           0x80000000);

    ecore_init_block(sc, BLOCK_UPB, PHASE_COMMON);
    ecore_init_block(sc, BLOCK_XPB, PHASE_COMMON);
    ecore_init_block(sc, BLOCK_PBF, PHASE_COMMON);

    if (!CHIP_IS_E1x(sc)) {
        if (IS_MF_AFEX(sc)) {
            /*
             * configure that AFEX and VLAN headers must be
             * sent in AFEX mode
             */
            REG_WR(sc, PBF_REG_HDRS_AFTER_BASIC, 0xE);
            REG_WR(sc, PBF_REG_MUST_HAVE_HDRS, 0xA);
            REG_WR(sc, PBF_REG_HDRS_AFTER_TAG_0, 0x6);
            REG_WR(sc, PBF_REG_TAG_ETHERTYPE_0, 0x8926);
            REG_WR(sc, PBF_REG_TAG_LEN_0, 0x4);
        } else {
            REG_WR(sc, PBF_REG_HDRS_AFTER_BASIC,
                   sc->devinfo.mf_info.path_has_ovlan ? 7 : 6);
        }
    }

    REG_WR(sc, SRC_REG_SOFT_RST, 1);

    ecore_init_block(sc, BLOCK_SRC, PHASE_COMMON);

    if (CNIC_SUPPORT(sc)) {
        REG_WR(sc, SRC_REG_KEYSEARCH_0, 0x63285672);
        REG_WR(sc, SRC_REG_KEYSEARCH_1, 0x24b8f2cc);
        REG_WR(sc, SRC_REG_KEYSEARCH_2, 0x223aef9b);
        REG_WR(sc, SRC_REG_KEYSEARCH_3, 0x26001e3a);
        REG_WR(sc, SRC_REG_KEYSEARCH_4, 0x7ae91116);
        REG_WR(sc, SRC_REG_KEYSEARCH_5, 0x5ce5230b);
        REG_WR(sc, SRC_REG_KEYSEARCH_6, 0x298d8adf);
        REG_WR(sc, SRC_REG_KEYSEARCH_7, 0x6eb0ff09);
        REG_WR(sc, SRC_REG_KEYSEARCH_8, 0x1830f82f);
        REG_WR(sc, SRC_REG_KEYSEARCH_9, 0x01e46be7);
    }
    REG_WR(sc, SRC_REG_SOFT_RST, 0);

    if (sizeof(union cdu_context) != 1024) {
        /* we currently assume that a context is 1024 bytes */
        BLOGE(sc, "please adjust the size of cdu_context(%ld)\n",
              (long)sizeof(union cdu_context));
    }

    ecore_init_block(sc, BLOCK_CDU, PHASE_COMMON);
    val = (4 << 24) + (0 << 12) + 1024;
    REG_WR(sc, CDU_REG_CDU_GLOBAL_PARAMS, val);

    ecore_init_block(sc, BLOCK_CFC, PHASE_COMMON);

    REG_WR(sc, CFC_REG_INIT_REG, 0x7FF);
    /* enable context validation interrupt from CFC */
    REG_WR(sc, CFC_REG_CFC_INT_MASK, 0);

    /* set the thresholds to prevent CFC/CDU race */
    REG_WR(sc, CFC_REG_DEBUG0, 0x20020000);
    ecore_init_block(sc, BLOCK_HC, PHASE_COMMON);

    if (!CHIP_IS_E1x(sc) && BXE_NOMCP(sc)) {
        REG_WR(sc, IGU_REG_RESET_MEMORIES, 0x36);
    }

    ecore_init_block(sc, BLOCK_IGU, PHASE_COMMON);
    ecore_init_block(sc, BLOCK_MISC_AEU, PHASE_COMMON);

    /* Reset PCIE errors for debug */
    REG_WR(sc, 0x2814, 0xffffffff);
    REG_WR(sc, 0x3820, 0xffffffff);

    if (!CHIP_IS_E1x(sc)) {
        REG_WR(sc, PCICFG_OFFSET + PXPCS_TL_CONTROL_5,
               (PXPCS_TL_CONTROL_5_ERR_UNSPPORT1 |
                PXPCS_TL_CONTROL_5_ERR_UNSPPORT));
        REG_WR(sc, PCICFG_OFFSET + PXPCS_TL_FUNC345_STAT,
               (PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT4 |
                PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT3 |
                PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT2));
        REG_WR(sc, PCICFG_OFFSET + PXPCS_TL_FUNC678_STAT,
               (PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT7 |
                PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT6 |
                PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT5));
    }

    ecore_init_block(sc, BLOCK_NIG, PHASE_COMMON);

    if (!CHIP_IS_E1(sc)) {
        /* in E3 this done in per-port section */
        if (!CHIP_IS_E3(sc))
            REG_WR(sc, NIG_REG_LLH_MF_MODE, IS_MF(sc));
    }

    if (CHIP_IS_E1H(sc)) {
        /* not applicable for E2 (and above ...) */
        REG_WR(sc, NIG_REG_LLH_E1HOV_MODE, IS_MF_SD(sc));
    }

    if (CHIP_REV_IS_SLOW(sc)) {
        DELAY(200000);
    }

    /* finish CFC init */
    val = reg_poll(sc, CFC_REG_LL_INIT_DONE, 1, 100, 10);
    if (val != 1) {
        BLOGE(sc, "CFC LL_INIT failed val=0x%x\n", val);
        return (-1);
    }
    val = reg_poll(sc, CFC_REG_AC_INIT_DONE, 1, 100, 10);
    if (val != 1) {
        BLOGE(sc, "CFC AC_INIT failed val=0x%x\n", val);
        return (-1);
    }
    val = reg_poll(sc, CFC_REG_CAM_INIT_DONE, 1, 100, 10);
    if (val != 1) {
        BLOGE(sc, "CFC CAM_INIT failed val=0x%x\n", val);
        return (-1);
    }
    REG_WR(sc, CFC_REG_DEBUG0, 0);

    if (CHIP_IS_E1(sc)) {
        /* read NIG statistic to see if this is our first up since powerup */
        bxe_read_dmae(sc, NIG_REG_STAT2_BRB_OCTET, 2);
        val = *BXE_SP(sc, wb_data[0]);

        /* do internal memory self test */
        if ((val == 0) && bxe_int_mem_test(sc)) {
            BLOGE(sc, "internal mem self test failed val=0x%x\n", val);
            return (-1);
        }
    }

    bxe_setup_fan_failure_detection(sc);

    /* clear PXP2 attentions */
    REG_RD(sc, PXP2_REG_PXP2_INT_STS_CLR_0);

    bxe_enable_blocks_attention(sc);

    if (!CHIP_REV_IS_SLOW(sc)) {
        ecore_enable_blocks_parity(sc);
    }

    if (!BXE_NOMCP(sc)) {
        if (CHIP_IS_E1x(sc)) {
            bxe_common_init_phy(sc);
        }
    }

    return (0);
}