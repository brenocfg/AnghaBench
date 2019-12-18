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
 int /*<<< orphan*/  BLOCK_BRB1 ; 
 int /*<<< orphan*/  BLOCK_PRS ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int) ; 
 int* BXE_SP (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ CFC_REG_DEBUG0 ; 
 scalar_t__ CHIP_REV_IS_EMUL (struct bxe_softc*) ; 
 scalar_t__ CHIP_REV_IS_FPGA (struct bxe_softc*) ; 
 int /*<<< orphan*/  CNIC_SUPPORT (struct bxe_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ GRCBASE_MISC ; 
 scalar_t__ MISC_REGISTERS_RESET_REG_1_CLEAR ; 
 scalar_t__ MISC_REGISTERS_RESET_REG_1_SET ; 
 int /*<<< orphan*/  NIG_REG_INGRESS_EOP_LB_EMPTY ; 
 int /*<<< orphan*/  NIG_REG_INGRESS_EOP_LB_FIFO ; 
 scalar_t__ NIG_REG_PRS_REQ_IN_EN ; 
 int /*<<< orphan*/  NIG_REG_STAT2_BRB_OCTET ; 
 int /*<<< orphan*/  PHASE_COMMON ; 
 scalar_t__ PRS_REG_CFC_SEARCH_INITIAL_CREDIT ; 
 scalar_t__ PRS_REG_NIC_MODE ; 
 int /*<<< orphan*/  PRS_REG_NUM_OF_PACKETS ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 
 scalar_t__ TCM_REG_PRS_IFEN ; 
 scalar_t__ TSDM_REG_ENABLE_IN1 ; 
 int /*<<< orphan*/  bxe_lb_pckt (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_read_dmae (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_init_block (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wb_data ; 

__attribute__((used)) static int
bxe_int_mem_test(struct bxe_softc *sc)
{
    int factor;
    int count, i;
    uint32_t val = 0;

    if (CHIP_REV_IS_FPGA(sc)) {
        factor = 120;
    } else if (CHIP_REV_IS_EMUL(sc)) {
        factor = 200;
    } else {
        factor = 1;
    }

    /* disable inputs of parser neighbor blocks */
    REG_WR(sc, TSDM_REG_ENABLE_IN1, 0x0);
    REG_WR(sc, TCM_REG_PRS_IFEN, 0x0);
    REG_WR(sc, CFC_REG_DEBUG0, 0x1);
    REG_WR(sc, NIG_REG_PRS_REQ_IN_EN, 0x0);

    /*  write 0 to parser credits for CFC search request */
    REG_WR(sc, PRS_REG_CFC_SEARCH_INITIAL_CREDIT, 0x0);

    /* send Ethernet packet */
    bxe_lb_pckt(sc);

    /* TODO do i reset NIG statistic? */
    /* Wait until NIG register shows 1 packet of size 0x10 */
    count = 1000 * factor;
    while (count) {
        bxe_read_dmae(sc, NIG_REG_STAT2_BRB_OCTET, 2);
        val = *BXE_SP(sc, wb_data[0]);
        if (val == 0x10) {
            break;
        }

        DELAY(10000);
        count--;
    }

    if (val != 0x10) {
        BLOGE(sc, "NIG timeout val=0x%x\n", val);
        return (-1);
    }

    /* wait until PRS register shows 1 packet */
    count = (1000 * factor);
    while (count) {
        val = REG_RD(sc, PRS_REG_NUM_OF_PACKETS);
        if (val == 1) {
            break;
        }

        DELAY(10000);
        count--;
    }

    if (val != 0x1) {
        BLOGE(sc, "PRS timeout val=0x%x\n", val);
        return (-2);
    }

    /* Reset and init BRB, PRS */
    REG_WR(sc, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_CLEAR, 0x03);
    DELAY(50000);
    REG_WR(sc, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_SET, 0x03);
    DELAY(50000);
    ecore_init_block(sc, BLOCK_BRB1, PHASE_COMMON);
    ecore_init_block(sc, BLOCK_PRS, PHASE_COMMON);

    /* Disable inputs of parser neighbor blocks */
    REG_WR(sc, TSDM_REG_ENABLE_IN1, 0x0);
    REG_WR(sc, TCM_REG_PRS_IFEN, 0x0);
    REG_WR(sc, CFC_REG_DEBUG0, 0x1);
    REG_WR(sc, NIG_REG_PRS_REQ_IN_EN, 0x0);

    /* Write 0 to parser credits for CFC search request */
    REG_WR(sc, PRS_REG_CFC_SEARCH_INITIAL_CREDIT, 0x0);

    /* send 10 Ethernet packets */
    for (i = 0; i < 10; i++) {
        bxe_lb_pckt(sc);
    }

    /* Wait until NIG register shows 10+1 packets of size 11*0x10 = 0xb0 */
    count = (1000 * factor);
    while (count) {
        bxe_read_dmae(sc, NIG_REG_STAT2_BRB_OCTET, 2);
        val = *BXE_SP(sc, wb_data[0]);
        if (val == 0xb0) {
            break;
        }

        DELAY(10000);
        count--;
    }

    if (val != 0xb0) {
        BLOGE(sc, "NIG timeout val=0x%x\n", val);
        return (-3);
    }

    /* Wait until PRS register shows 2 packets */
    val = REG_RD(sc, PRS_REG_NUM_OF_PACKETS);
    if (val != 2) {
        BLOGE(sc, "PRS timeout val=0x%x\n", val);
    }

    /* Write 1 to parser credits for CFC search request */
    REG_WR(sc, PRS_REG_CFC_SEARCH_INITIAL_CREDIT, 0x1);

    /* Wait until PRS register shows 3 packets */
    DELAY(10000 * factor);

    /* Wait until NIG register shows 1 packet of size 0x10 */
    val = REG_RD(sc, PRS_REG_NUM_OF_PACKETS);
    if (val != 3) {
        BLOGE(sc, "PRS timeout val=0x%x\n", val);
    }

    /* clear NIG EOP FIFO */
    for (i = 0; i < 11; i++) {
        REG_RD(sc, NIG_REG_INGRESS_EOP_LB_FIFO);
    }

    val = REG_RD(sc, NIG_REG_INGRESS_EOP_LB_EMPTY);
    if (val != 1) {
        BLOGE(sc, "clear of NIG failed val=0x%x\n", val);
        return (-4);
    }

    /* Reset and init BRB, PRS, NIG */
    REG_WR(sc, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_CLEAR, 0x03);
    DELAY(50000);
    REG_WR(sc, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_SET, 0x03);
    DELAY(50000);
    ecore_init_block(sc, BLOCK_BRB1, PHASE_COMMON);
    ecore_init_block(sc, BLOCK_PRS, PHASE_COMMON);
    if (!CNIC_SUPPORT(sc)) {
        /* set NIC mode */
        REG_WR(sc, PRS_REG_NIC_MODE, 1);
    }

    /* Enable inputs of parser neighbor blocks */
    REG_WR(sc, TSDM_REG_ENABLE_IN1, 0x7fffffff);
    REG_WR(sc, TCM_REG_PRS_IFEN, 0x1);
    REG_WR(sc, CFC_REG_DEBUG0, 0x0);
    REG_WR(sc, NIG_REG_PRS_REQ_IN_EN, 0x1);

    return (0);
}