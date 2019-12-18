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

/* Variables and functions */
 scalar_t__ BIGMAC2_REGISTER_BMAC_CONTROL ; 
 scalar_t__ BIGMAC_REGISTER_BMAC_CONTROL ; 
 scalar_t__ CHIP_IS_E2 (struct bxe_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ELINK_BMAC_CONTROL_RX_ENABLE ; 
 int MISC_REGISTERS_RESET_REG_2_RST_BMAC0 ; 
 scalar_t__ MISC_REG_RESET_REG_2 ; 
 scalar_t__ NIG_REG_BMAC0_REGS_OUT_EN ; 
 int NIG_REG_INGRESS_BMAC0_MEM ; 
 int NIG_REG_INGRESS_BMAC1_MEM ; 
 int REG_RD (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  REG_RD_DMAE (struct bxe_softc*,int,int*,int) ; 
 int /*<<< orphan*/  REG_WR_DMAE (struct bxe_softc*,int,int*,int) ; 

__attribute__((used)) static void elink_set_bmac_rx(struct bxe_softc *sc, uint32_t chip_id, uint8_t port, uint8_t en)
{
	uint32_t bmac_addr = port ? NIG_REG_INGRESS_BMAC1_MEM :
			NIG_REG_INGRESS_BMAC0_MEM;
	uint32_t wb_data[2];
	uint32_t nig_bmac_enable = REG_RD(sc, NIG_REG_BMAC0_REGS_OUT_EN + port*4);

	if (CHIP_IS_E2(sc))
		bmac_addr += BIGMAC2_REGISTER_BMAC_CONTROL;
	else
		bmac_addr += BIGMAC_REGISTER_BMAC_CONTROL;
	/* Only if the bmac is out of reset */
	if (REG_RD(sc, MISC_REG_RESET_REG_2) &
			(MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << port) &&
	    nig_bmac_enable) {
		/* Clear Rx Enable bit in BMAC_CONTROL register */
		REG_RD_DMAE(sc, bmac_addr, wb_data, 2);
		if (en)
			wb_data[0] |= ELINK_BMAC_CONTROL_RX_ENABLE;
		else
			wb_data[0] &= ~ELINK_BMAC_CONTROL_RX_ENABLE;
		REG_WR_DMAE(sc, bmac_addr, wb_data, 2);
		DELAY(1000 * 1);
	}
}