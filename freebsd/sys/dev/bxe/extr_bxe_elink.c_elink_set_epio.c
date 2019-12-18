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
 int /*<<< orphan*/  ELINK_DEBUG_P1 (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  ELINK_DEBUG_P2 (struct bxe_softc*,char*,int,int) ; 
 int /*<<< orphan*/  MCP_REG_MCPR_GP_OENABLE ; 
 int /*<<< orphan*/  MCP_REG_MCPR_GP_OUTPUTS ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void elink_set_epio(struct bxe_softc *sc, uint32_t epio_pin, uint32_t en)
{
	uint32_t epio_mask, gp_output, gp_oenable;

	/* Sanity check */
	if (epio_pin > 31) {
		ELINK_DEBUG_P1(sc, "Invalid EPIO pin %d to set\n", epio_pin);
		return;
	}
	ELINK_DEBUG_P2(sc, "Setting EPIO pin %d to %d\n", epio_pin, en);
	epio_mask = 1 << epio_pin;
	/* Set this EPIO to output */
	gp_output = REG_RD(sc, MCP_REG_MCPR_GP_OUTPUTS);
	if (en)
		gp_output |= epio_mask;
	else
		gp_output &= ~epio_mask;

	REG_WR(sc, MCP_REG_MCPR_GP_OUTPUTS, gp_output);

	/* Set the value for this EPIO */
	gp_oenable = REG_RD(sc, MCP_REG_MCPR_GP_OENABLE);
	REG_WR(sc, MCP_REG_MCPR_GP_OENABLE, gp_oenable | epio_mask);
}