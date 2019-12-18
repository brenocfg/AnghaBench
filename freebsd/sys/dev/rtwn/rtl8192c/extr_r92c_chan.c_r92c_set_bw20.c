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
struct rtwn_softc {struct r92c_softc* sc_priv; } ;
struct r92c_softc {int* rf_chnlbw; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_BWOPMODE ; 
 int /*<<< orphan*/  R92C_BWOPMODE_20MHZ ; 
 int /*<<< orphan*/  R92C_FPGA0_ANAPARAM2 ; 
 int /*<<< orphan*/  R92C_FPGA0_ANAPARAM2_CBW20 ; 
 int /*<<< orphan*/  R92C_FPGA0_RFMOD ; 
 int /*<<< orphan*/  R92C_FPGA1_RFMOD ; 
 int /*<<< orphan*/  R92C_RFMOD_40MHZ ; 
 int /*<<< orphan*/  R92C_RF_CHNLBW ; 
 int R92C_RF_CHNLBW_BW20 ; 
 int /*<<< orphan*/  rtwn_bb_setbits (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_rf_write (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
r92c_set_bw20(struct rtwn_softc *sc, uint8_t chan)
{
	struct r92c_softc *rs = sc->sc_priv;

	rtwn_setbits_1(sc, R92C_BWOPMODE, 0, R92C_BWOPMODE_20MHZ);

	rtwn_bb_setbits(sc, R92C_FPGA0_RFMOD, R92C_RFMOD_40MHZ, 0);
	rtwn_bb_setbits(sc, R92C_FPGA1_RFMOD, R92C_RFMOD_40MHZ, 0);

	rtwn_bb_setbits(sc, R92C_FPGA0_ANAPARAM2, 0,
	    R92C_FPGA0_ANAPARAM2_CBW20);

	/* Select 20MHz bandwidth. */
	rtwn_rf_write(sc, 0, R92C_RF_CHNLBW,
	    (rs->rf_chnlbw[0] & ~0xfff) | chan | R92C_RF_CHNLBW_BW20);
}