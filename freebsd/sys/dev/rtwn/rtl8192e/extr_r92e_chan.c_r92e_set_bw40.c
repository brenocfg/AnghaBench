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
struct rtwn_softc {int nrxchains; } ;

/* Variables and functions */
 int /*<<< orphan*/  R12A_DATA_SEC ; 
 int /*<<< orphan*/  R12A_DATA_SEC_PRIM_DOWN_20 ; 
 int /*<<< orphan*/  R12A_DATA_SEC_PRIM_UP_20 ; 
 int /*<<< orphan*/  R88E_RF_CHNLBW_BW20 ; 
 int R92C_CCK0_SYSTEM ; 
 int R92C_CCK0_SYSTEM_CCK_SIDEBAND ; 
 int R92C_FPGA0_ANAPARAM2 ; 
 int R92C_FPGA0_ANAPARAM2_CBW20 ; 
 int R92C_FPGA0_RFMOD ; 
 int R92C_FPGA1_RFMOD ; 
 int R92C_OFDM1_LSTF ; 
 int R92C_RFMOD_40MHZ ; 
 int /*<<< orphan*/  R92C_RF_CHNLBW ; 
 int /*<<< orphan*/  R92C_WMAC_TRXPTCL_CTL ; 
 int /*<<< orphan*/  rtwn_bb_setbits (struct rtwn_softc*,int,int,int) ; 
 int /*<<< orphan*/  rtwn_rf_setbits (struct rtwn_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_setbits_2 (struct rtwn_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
r92e_set_bw40(struct rtwn_softc *sc, uint8_t chan, int prichlo)
{
	int i;

	rtwn_setbits_2(sc, R92C_WMAC_TRXPTCL_CTL, 0x100, 0x80);
	rtwn_write_1(sc, R12A_DATA_SEC,
	    prichlo ? R12A_DATA_SEC_PRIM_DOWN_20 : R12A_DATA_SEC_PRIM_UP_20);

	rtwn_bb_setbits(sc, R92C_FPGA0_RFMOD, 0, R92C_RFMOD_40MHZ);
	rtwn_bb_setbits(sc, R92C_FPGA1_RFMOD, 0, R92C_RFMOD_40MHZ);

	/* Select 40MHz bandwidth. */
	for (i = 0; i < sc->nrxchains; i++)
		rtwn_rf_setbits(sc, i, R92C_RF_CHNLBW,
		    R88E_RF_CHNLBW_BW20, 0x400);

	/* Set CCK side band. */
	rtwn_bb_setbits(sc, R92C_CCK0_SYSTEM,
	    R92C_CCK0_SYSTEM_CCK_SIDEBAND, (prichlo ? 0 : 1) << 4);
		
	rtwn_bb_setbits(sc, R92C_OFDM1_LSTF, 0x0c00, (prichlo ? 1 : 2) << 10);

	rtwn_bb_setbits(sc, R92C_FPGA0_ANAPARAM2,
	    R92C_FPGA0_ANAPARAM2_CBW20, 0);

	rtwn_bb_setbits(sc, 0x818, 0x0c000000, (prichlo ? 2 : 1) << 26);
}