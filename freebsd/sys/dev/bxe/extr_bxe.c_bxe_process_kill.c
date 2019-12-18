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
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  CHIP_IS_E1 (struct bxe_softc*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MISC_REG_UNPREPARED ; 
 int /*<<< orphan*/  PGLUE_B_REG_LATCHED_ERRORS_CLR ; 
 int /*<<< orphan*/  PGLUE_B_REG_TAGS_63_32 ; 
 int /*<<< orphan*/  PXP2_REG_PGL_EXP_ROM2 ; 
 int /*<<< orphan*/  PXP2_REG_RD_BLK_CNT ; 
 int /*<<< orphan*/  PXP2_REG_RD_PORT_IS_IDLE_0 ; 
 int /*<<< orphan*/  PXP2_REG_RD_PORT_IS_IDLE_1 ; 
 int /*<<< orphan*/  PXP2_REG_RD_SR_CNT ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bxe_er_poll_igu_vq (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_process_kill_chip_reset (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_pxp_prep (struct bxe_softc*) ; 
 scalar_t__ bxe_reset_mcp_comp (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  bxe_reset_mcp_prep (struct bxe_softc*,int*) ; 
 int /*<<< orphan*/  bxe_set_234_gates (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
bxe_process_kill(struct bxe_softc *sc,
                 uint8_t          global)
{
    int cnt = 1000;
    uint32_t val = 0;
    uint32_t sr_cnt, blk_cnt, port_is_idle_0, port_is_idle_1, pgl_exp_rom2;
    uint32_t tags_63_32 = 0;

    /* Empty the Tetris buffer, wait for 1s */
    do {
        sr_cnt  = REG_RD(sc, PXP2_REG_RD_SR_CNT);
        blk_cnt = REG_RD(sc, PXP2_REG_RD_BLK_CNT);
        port_is_idle_0 = REG_RD(sc, PXP2_REG_RD_PORT_IS_IDLE_0);
        port_is_idle_1 = REG_RD(sc, PXP2_REG_RD_PORT_IS_IDLE_1);
        pgl_exp_rom2 = REG_RD(sc, PXP2_REG_PGL_EXP_ROM2);
        if (CHIP_IS_E3(sc)) {
            tags_63_32 = REG_RD(sc, PGLUE_B_REG_TAGS_63_32);
        }

        if ((sr_cnt == 0x7e) && (blk_cnt == 0xa0) &&
            ((port_is_idle_0 & 0x1) == 0x1) &&
            ((port_is_idle_1 & 0x1) == 0x1) &&
            (pgl_exp_rom2 == 0xffffffff) &&
            (!CHIP_IS_E3(sc) || (tags_63_32 == 0xffffffff)))
            break;
        DELAY(1000);
    } while (cnt-- > 0);

    if (cnt <= 0) {
        BLOGE(sc, "ERROR: Tetris buffer didn't get empty or there "
                  "are still outstanding read requests after 1s! "
                  "sr_cnt=0x%08x, blk_cnt=0x%08x, port_is_idle_0=0x%08x, "
                  "port_is_idle_1=0x%08x, pgl_exp_rom2=0x%08x\n",
              sr_cnt, blk_cnt, port_is_idle_0,
              port_is_idle_1, pgl_exp_rom2);
        return (-1);
    }

    mb();

    /* Close gates #2, #3 and #4 */
    bxe_set_234_gates(sc, TRUE);

    /* Poll for IGU VQs for 57712 and newer chips */
    if (!CHIP_IS_E1x(sc) && bxe_er_poll_igu_vq(sc)) {
        return (-1);
    }

    /* XXX indicate that "process kill" is in progress to MCP */

    /* clear "unprepared" bit */
    REG_WR(sc, MISC_REG_UNPREPARED, 0);
    mb();

    /* Make sure all is written to the chip before the reset */
    wmb();

    /*
     * Wait for 1ms to empty GLUE and PCI-E core queues,
     * PSWHST, GRC and PSWRD Tetris buffer.
     */
    DELAY(1000);

    /* Prepare to chip reset: */
    /* MCP */
    if (global) {
        bxe_reset_mcp_prep(sc, &val);
    }

    /* PXP */
    bxe_pxp_prep(sc);
    mb();

    /* reset the chip */
    bxe_process_kill_chip_reset(sc, global);
    mb();

    /* clear errors in PGB */
    if (!CHIP_IS_E1(sc))
        REG_WR(sc, PGLUE_B_REG_LATCHED_ERRORS_CLR, 0x7f);

    /* Recover after reset: */
    /* MCP */
    if (global && bxe_reset_mcp_comp(sc, val)) {
        return (-1);
    }

    /* XXX add resetting the NO_MCP mode DB here */

    /* Open the gates #2, #3 and #4 */
    bxe_set_234_gates(sc, FALSE);

    /* XXX
     * IGU/AEU preparation bring back the AEU/IGU to a reset state
     * re-enable attentions
     */

    return (0);
}