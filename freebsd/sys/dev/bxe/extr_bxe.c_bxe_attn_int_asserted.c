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
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ int_block; } ;
struct bxe_softc {int attn_state; TYPE_1__ devinfo; } ;

/* Variables and functions */
 int ATTN_GENERAL_ATTN_1 ; 
 int ATTN_GENERAL_ATTN_2 ; 
 int ATTN_GENERAL_ATTN_3 ; 
 int ATTN_GENERAL_ATTN_4 ; 
 int ATTN_GENERAL_ATTN_5 ; 
 int ATTN_GENERAL_ATTN_6 ; 
 int ATTN_HARD_WIRED_MASK ; 
 int ATTN_NIG_FOR_FUNC ; 
 int ATTN_SW_TIMER_4_FUNC ; 
 int BAR_IGU_INTMEM ; 
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,...) ; 
 int COMMAND_REG_ATTN_BITS_SET ; 
 int /*<<< orphan*/  DBG_INTR ; 
 int GPIO_2_FUNC ; 
 int GPIO_3_FUNC ; 
 int GPIO_4_FUNC ; 
 int HC_REG_COMMAND_REG ; 
 scalar_t__ HW_LOCK_RESOURCE_PORT0_ATT_MASK ; 
 int IGU_CMD_ATTN_BIT_SET_UPPER ; 
 int IGU_REG_ATTENTION_ACK_BITS ; 
 scalar_t__ INT_BLOCK_HC ; 
 int MAX_IGU_ATTN_ACK_TO ; 
 int MISC_REG_AEU_GENERAL_ATTN_1 ; 
 int MISC_REG_AEU_GENERAL_ATTN_2 ; 
 int MISC_REG_AEU_GENERAL_ATTN_3 ; 
 int MISC_REG_AEU_GENERAL_ATTN_4 ; 
 int MISC_REG_AEU_GENERAL_ATTN_5 ; 
 int MISC_REG_AEU_GENERAL_ATTN_6 ; 
 int MISC_REG_AEU_MASK_ATTN_FUNC_0 ; 
 int MISC_REG_AEU_MASK_ATTN_FUNC_1 ; 
 int NIG_REG_MASK_INTERRUPT_PORT0 ; 
 int NIG_REG_MASK_INTERRUPT_PORT1 ; 
 int REG_RD (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 
 int SC_PORT (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_acquire_hw_lock (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  bxe_acquire_phy_lock (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_link_attn (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_release_hw_lock (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  bxe_release_phy_lock (struct bxe_softc*) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void
bxe_attn_int_asserted(struct bxe_softc *sc,
                      uint32_t         asserted)
{
    int port = SC_PORT(sc);
    uint32_t aeu_addr = port ? MISC_REG_AEU_MASK_ATTN_FUNC_1 :
                               MISC_REG_AEU_MASK_ATTN_FUNC_0;
    uint32_t nig_int_mask_addr = port ? NIG_REG_MASK_INTERRUPT_PORT1 :
                                        NIG_REG_MASK_INTERRUPT_PORT0;
    uint32_t aeu_mask;
    uint32_t nig_mask = 0;
    uint32_t reg_addr;
    uint32_t igu_acked;
    uint32_t cnt;

    if (sc->attn_state & asserted) {
        BLOGE(sc, "IGU ERROR attn=0x%08x\n", asserted);
    }

    bxe_acquire_hw_lock(sc, HW_LOCK_RESOURCE_PORT0_ATT_MASK + port);

    aeu_mask = REG_RD(sc, aeu_addr);

    BLOGD(sc, DBG_INTR, "aeu_mask 0x%08x newly asserted 0x%08x\n",
          aeu_mask, asserted);

    aeu_mask &= ~(asserted & 0x3ff);

    BLOGD(sc, DBG_INTR, "new mask 0x%08x\n", aeu_mask);

    REG_WR(sc, aeu_addr, aeu_mask);

    bxe_release_hw_lock(sc, HW_LOCK_RESOURCE_PORT0_ATT_MASK + port);

    BLOGD(sc, DBG_INTR, "attn_state 0x%08x\n", sc->attn_state);
    sc->attn_state |= asserted;
    BLOGD(sc, DBG_INTR, "new state 0x%08x\n", sc->attn_state);

    if (asserted & ATTN_HARD_WIRED_MASK) {
        if (asserted & ATTN_NIG_FOR_FUNC) {

	    bxe_acquire_phy_lock(sc);
            /* save nig interrupt mask */
            nig_mask = REG_RD(sc, nig_int_mask_addr);

            /* If nig_mask is not set, no need to call the update function */
            if (nig_mask) {
                REG_WR(sc, nig_int_mask_addr, 0);

                bxe_link_attn(sc);
            }

            /* handle unicore attn? */
        }

        if (asserted & ATTN_SW_TIMER_4_FUNC) {
            BLOGD(sc, DBG_INTR, "ATTN_SW_TIMER_4_FUNC!\n");
        }

        if (asserted & GPIO_2_FUNC) {
            BLOGD(sc, DBG_INTR, "GPIO_2_FUNC!\n");
        }

        if (asserted & GPIO_3_FUNC) {
            BLOGD(sc, DBG_INTR, "GPIO_3_FUNC!\n");
        }

        if (asserted & GPIO_4_FUNC) {
            BLOGD(sc, DBG_INTR, "GPIO_4_FUNC!\n");
        }

        if (port == 0) {
            if (asserted & ATTN_GENERAL_ATTN_1) {
                BLOGD(sc, DBG_INTR, "ATTN_GENERAL_ATTN_1!\n");
                REG_WR(sc, MISC_REG_AEU_GENERAL_ATTN_1, 0x0);
            }
            if (asserted & ATTN_GENERAL_ATTN_2) {
                BLOGD(sc, DBG_INTR, "ATTN_GENERAL_ATTN_2!\n");
                REG_WR(sc, MISC_REG_AEU_GENERAL_ATTN_2, 0x0);
            }
            if (asserted & ATTN_GENERAL_ATTN_3) {
                BLOGD(sc, DBG_INTR, "ATTN_GENERAL_ATTN_3!\n");
                REG_WR(sc, MISC_REG_AEU_GENERAL_ATTN_3, 0x0);
            }
        } else {
            if (asserted & ATTN_GENERAL_ATTN_4) {
                BLOGD(sc, DBG_INTR, "ATTN_GENERAL_ATTN_4!\n");
                REG_WR(sc, MISC_REG_AEU_GENERAL_ATTN_4, 0x0);
            }
            if (asserted & ATTN_GENERAL_ATTN_5) {
                BLOGD(sc, DBG_INTR, "ATTN_GENERAL_ATTN_5!\n");
                REG_WR(sc, MISC_REG_AEU_GENERAL_ATTN_5, 0x0);
            }
            if (asserted & ATTN_GENERAL_ATTN_6) {
                BLOGD(sc, DBG_INTR, "ATTN_GENERAL_ATTN_6!\n");
                REG_WR(sc, MISC_REG_AEU_GENERAL_ATTN_6, 0x0);
            }
        }
    } /* hardwired */

    if (sc->devinfo.int_block == INT_BLOCK_HC) {
        reg_addr = (HC_REG_COMMAND_REG + port*32 + COMMAND_REG_ATTN_BITS_SET);
    } else {
        reg_addr = (BAR_IGU_INTMEM + IGU_CMD_ATTN_BIT_SET_UPPER*8);
    }

    BLOGD(sc, DBG_INTR, "about to mask 0x%08x at %s addr 0x%08x\n",
          asserted,
          (sc->devinfo.int_block == INT_BLOCK_HC) ? "HC" : "IGU", reg_addr);
    REG_WR(sc, reg_addr, asserted);

    /* now set back the mask */
    if (asserted & ATTN_NIG_FOR_FUNC) {
        /*
         * Verify that IGU ack through BAR was written before restoring
         * NIG mask. This loop should exit after 2-3 iterations max.
         */
        if (sc->devinfo.int_block != INT_BLOCK_HC) {
            cnt = 0;

            do {
                igu_acked = REG_RD(sc, IGU_REG_ATTENTION_ACK_BITS);
            } while (((igu_acked & ATTN_NIG_FOR_FUNC) == 0) &&
                     (++cnt < MAX_IGU_ATTN_ACK_TO));

            if (!igu_acked) {
                BLOGE(sc, "Failed to verify IGU ack on time\n");
            }

            mb();
        }

        REG_WR(sc, nig_int_mask_addr, nig_mask);

	bxe_release_phy_lock(sc);
    }
}