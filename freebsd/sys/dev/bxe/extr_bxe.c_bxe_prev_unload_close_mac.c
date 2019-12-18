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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;
struct bxe_mac_vals {int bmac_addr; int umac_addr; int xmac_addr; int emac_addr; int* bmac_val; void* umac_val; void* xmac_val; void* emac_val; } ;

/* Variables and functions */
 int BIGMAC2_REGISTER_BMAC_CONTROL ; 
 int BIGMAC_REGISTER_BMAC_CONTROL ; 
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ CHIP_IS_E2 (struct bxe_softc*) ; 
 int /*<<< orphan*/  CHIP_IS_E3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ELINK_BMAC_CONTROL_RX_ENABLE ; 
 int FALSE ; 
 int GRCBASE_UMAC0 ; 
 int GRCBASE_UMAC1 ; 
 int GRCBASE_XMAC0 ; 
 int GRCBASE_XMAC1 ; 
 int MISC_REGISTERS_RESET_REG_2_RST_BMAC0 ; 
 int MISC_REGISTERS_RESET_REG_2_UMAC0 ; 
 int MISC_REGISTERS_RESET_REG_2_XMAC ; 
 int MISC_REG_RESET_REG_2 ; 
 int NIG_REG_BMAC0_REGS_OUT_EN ; 
 int NIG_REG_INGRESS_BMAC0_MEM ; 
 int NIG_REG_INGRESS_BMAC1_MEM ; 
 int NIG_REG_NIG_EMAC0_EN ; 
 void* REG_RD (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 
 int SC_PORT (struct bxe_softc*) ; 
 int TRUE ; 
 int UMAC_REG_COMMAND_CONFIG ; 
 int XMAC_REG_CTRL ; 
 int XMAC_REG_PFC_CTRL_HI ; 

__attribute__((used)) static void
bxe_prev_unload_close_mac(struct bxe_softc *sc,
                          struct bxe_mac_vals *vals)
{
    uint32_t val, base_addr, offset, mask, reset_reg;
    uint8_t mac_stopped = FALSE;
    uint8_t port = SC_PORT(sc);
    uint32_t wb_data[2];

    /* reset addresses as they also mark which values were changed */
    vals->bmac_addr = 0;
    vals->umac_addr = 0;
    vals->xmac_addr = 0;
    vals->emac_addr = 0;

    reset_reg = REG_RD(sc, MISC_REG_RESET_REG_2);

    if (!CHIP_IS_E3(sc)) {
        val = REG_RD(sc, NIG_REG_BMAC0_REGS_OUT_EN + port * 4);
        mask = MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << port;
        if ((mask & reset_reg) && val) {
            BLOGD(sc, DBG_LOAD, "Disable BMAC Rx\n");
            base_addr = SC_PORT(sc) ? NIG_REG_INGRESS_BMAC1_MEM
                                    : NIG_REG_INGRESS_BMAC0_MEM;
            offset = CHIP_IS_E2(sc) ? BIGMAC2_REGISTER_BMAC_CONTROL
                                    : BIGMAC_REGISTER_BMAC_CONTROL;

            /*
             * use rd/wr since we cannot use dmae. This is safe
             * since MCP won't access the bus due to the request
             * to unload, and no function on the path can be
             * loaded at this time.
             */
            wb_data[0] = REG_RD(sc, base_addr + offset);
            wb_data[1] = REG_RD(sc, base_addr + offset + 0x4);
            vals->bmac_addr = base_addr + offset;
            vals->bmac_val[0] = wb_data[0];
            vals->bmac_val[1] = wb_data[1];
            wb_data[0] &= ~ELINK_BMAC_CONTROL_RX_ENABLE;
            REG_WR(sc, vals->bmac_addr, wb_data[0]);
            REG_WR(sc, vals->bmac_addr + 0x4, wb_data[1]);
        }

        BLOGD(sc, DBG_LOAD, "Disable EMAC Rx\n");
        vals->emac_addr = NIG_REG_NIG_EMAC0_EN + SC_PORT(sc)*4;
        vals->emac_val = REG_RD(sc, vals->emac_addr);
        REG_WR(sc, vals->emac_addr, 0);
        mac_stopped = TRUE;
    } else {
        if (reset_reg & MISC_REGISTERS_RESET_REG_2_XMAC) {
            BLOGD(sc, DBG_LOAD, "Disable XMAC Rx\n");
            base_addr = SC_PORT(sc) ? GRCBASE_XMAC1 : GRCBASE_XMAC0;
            val = REG_RD(sc, base_addr + XMAC_REG_PFC_CTRL_HI);
            REG_WR(sc, base_addr + XMAC_REG_PFC_CTRL_HI, val & ~(1 << 1));
            REG_WR(sc, base_addr + XMAC_REG_PFC_CTRL_HI, val | (1 << 1));
            vals->xmac_addr = base_addr + XMAC_REG_CTRL;
            vals->xmac_val = REG_RD(sc, vals->xmac_addr);
            REG_WR(sc, vals->xmac_addr, 0);
            mac_stopped = TRUE;
        }

        mask = MISC_REGISTERS_RESET_REG_2_UMAC0 << port;
        if (mask & reset_reg) {
            BLOGD(sc, DBG_LOAD, "Disable UMAC Rx\n");
            base_addr = SC_PORT(sc) ? GRCBASE_UMAC1 : GRCBASE_UMAC0;
            vals->umac_addr = base_addr + UMAC_REG_COMMAND_CONFIG;
            vals->umac_val = REG_RD(sc, vals->umac_addr);
            REG_WR(sc, vals->umac_addr, 0);
            mac_stopped = TRUE;
        }
    }

    if (mac_stopped) {
        DELAY(20000);
    }
}