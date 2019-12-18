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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct bxe_softc {int /*<<< orphan*/  link_params; } ;
struct bxe_mac_vals {int /*<<< orphan*/ * bmac_val; scalar_t__ bmac_addr; int /*<<< orphan*/  emac_val; scalar_t__ emac_addr; int /*<<< orphan*/  umac_val; scalar_t__ umac_addr; int /*<<< orphan*/  xmac_val; scalar_t__ xmac_addr; } ;
typedef  int /*<<< orphan*/  mac_vals ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 scalar_t__ BRB1_REG_NUM_OF_FULL_BLOCKS ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ DORQ_REG_NORM_CID_OFST ; 
 scalar_t__ FALSE ; 
 int MISC_REGISTERS_RESET_REG_1_RST_BRB1 ; 
 int MISC_REGISTERS_RESET_REG_1_RST_DORQ ; 
 scalar_t__ MISC_REG_RESET_REG_1 ; 
 scalar_t__ NIG_REG_NIG_INT_STS_CLR_0 ; 
 int REG_RD (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_PORT (struct bxe_softc*) ; 
 scalar_t__ TRUE ; 
 scalar_t__ bxe_prev_is_path_marked (struct bxe_softc*) ; 
 int bxe_prev_mark_path (struct bxe_softc*,scalar_t__) ; 
 int bxe_prev_mcp_done (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_prev_unload_close_mac (struct bxe_softc*,struct bxe_mac_vals*) ; 
 int /*<<< orphan*/  bxe_prev_unload_undi_inc (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bxe_reset_common (struct bxe_softc*) ; 
 int /*<<< orphan*/  elink_set_rx_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bxe_mac_vals*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bxe_prev_unload_common(struct bxe_softc *sc)
{
    uint32_t reset_reg, tmp_reg = 0, rc;
    uint8_t prev_undi = FALSE;
    struct bxe_mac_vals mac_vals;
    uint32_t timer_count = 1000;
    uint32_t prev_brb;

    /*
     * It is possible a previous function received 'common' answer,
     * but hasn't loaded yet, therefore creating a scenario of
     * multiple functions receiving 'common' on the same path.
     */
    BLOGD(sc, DBG_LOAD, "Common unload Flow\n");

    memset(&mac_vals, 0, sizeof(mac_vals));

    if (bxe_prev_is_path_marked(sc)) {
        return (bxe_prev_mcp_done(sc));
    }

    reset_reg = REG_RD(sc, MISC_REG_RESET_REG_1);

    /* Reset should be performed after BRB is emptied */
    if (reset_reg & MISC_REGISTERS_RESET_REG_1_RST_BRB1) {
        /* Close the MAC Rx to prevent BRB from filling up */
        bxe_prev_unload_close_mac(sc, &mac_vals);

        /* close LLH filters towards the BRB */
        elink_set_rx_filter(&sc->link_params, 0);

        /*
         * Check if the UNDI driver was previously loaded.
         * UNDI driver initializes CID offset for normal bell to 0x7
         */
        if (reset_reg & MISC_REGISTERS_RESET_REG_1_RST_DORQ) {
            tmp_reg = REG_RD(sc, DORQ_REG_NORM_CID_OFST);
            if (tmp_reg == 0x7) {
                BLOGD(sc, DBG_LOAD, "UNDI previously loaded\n");
                prev_undi = TRUE;
                /* clear the UNDI indication */
                REG_WR(sc, DORQ_REG_NORM_CID_OFST, 0);
                /* clear possible idle check errors */
                REG_RD(sc, NIG_REG_NIG_INT_STS_CLR_0);
            }
        }

        /* wait until BRB is empty */
        tmp_reg = REG_RD(sc, BRB1_REG_NUM_OF_FULL_BLOCKS);
        while (timer_count) {
            prev_brb = tmp_reg;

            tmp_reg = REG_RD(sc, BRB1_REG_NUM_OF_FULL_BLOCKS);
            if (!tmp_reg) {
                break;
            }

            BLOGD(sc, DBG_LOAD, "BRB still has 0x%08x\n", tmp_reg);

            /* reset timer as long as BRB actually gets emptied */
            if (prev_brb > tmp_reg) {
                timer_count = 1000;
            } else {
                timer_count--;
            }

            /* If UNDI resides in memory, manually increment it */
            if (prev_undi) {
                bxe_prev_unload_undi_inc(sc, SC_PORT(sc), 1);
            }

            DELAY(10);
        }

        if (!timer_count) {
            BLOGE(sc, "Failed to empty BRB\n");
        }
    }

    /* No packets are in the pipeline, path is ready for reset */
    bxe_reset_common(sc);

    if (mac_vals.xmac_addr) {
        REG_WR(sc, mac_vals.xmac_addr, mac_vals.xmac_val);
    }
    if (mac_vals.umac_addr) {
        REG_WR(sc, mac_vals.umac_addr, mac_vals.umac_val);
    }
    if (mac_vals.emac_addr) {
        REG_WR(sc, mac_vals.emac_addr, mac_vals.emac_val);
    }
    if (mac_vals.bmac_addr) {
        REG_WR(sc, mac_vals.bmac_addr, mac_vals.bmac_val[0]);
        REG_WR(sc, mac_vals.bmac_addr + 4, mac_vals.bmac_val[1]);
    }

    rc = bxe_prev_mark_path(sc, prev_undi);
    if (rc) {
        bxe_prev_mcp_done(sc);
        return (rc);
    }

    return (bxe_prev_mcp_done(sc));
}