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
typedef  int /*<<< orphan*/  uint32_t ;
struct rtwn_softc {int /*<<< orphan*/  sc_ant; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_FPGA0_RFIFACEOE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_FPGA0_RFIFACEOE0_ANT ; 
 int /*<<< orphan*/  R92C_FPGA0_RFPARAM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_LEDCFG2 ; 
 int /*<<< orphan*/  rtwn_bb_read (struct rtwn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_bb_setbits (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
r12a_init_antsel(struct rtwn_softc *sc)
{
	uint32_t reg;

	rtwn_write_1(sc, R92C_LEDCFG2, 0x82);
	rtwn_bb_setbits(sc, R92C_FPGA0_RFPARAM(0), 0, 0x2000);
	reg = rtwn_bb_read(sc, R92C_FPGA0_RFIFACEOE(0));
	sc->sc_ant = MS(reg, R92C_FPGA0_RFIFACEOE0_ANT);
}