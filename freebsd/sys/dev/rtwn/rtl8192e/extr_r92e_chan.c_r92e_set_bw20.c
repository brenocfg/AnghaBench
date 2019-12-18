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
 int /*<<< orphan*/  R12A_DATA_SEC_NO_EXT ; 
 int /*<<< orphan*/  R88E_RF_CHNLBW_BW20 ; 
 int /*<<< orphan*/  R92C_FPGA0_RFMOD ; 
 int /*<<< orphan*/  R92C_FPGA1_RFMOD ; 
 int /*<<< orphan*/  R92C_OFDM0_TXPSEUDONOISEWGT ; 
 int R92C_RFMOD_40MHZ ; 
 int /*<<< orphan*/  R92C_RF_CHNLBW ; 
 int /*<<< orphan*/  R92C_WMAC_TRXPTCL_CTL ; 
 int /*<<< orphan*/  rtwn_bb_setbits (struct rtwn_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_rf_setbits (struct rtwn_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_setbits_2 (struct rtwn_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
r92e_set_bw20(struct rtwn_softc *sc, uint8_t chan)
{
	int i;

	rtwn_setbits_2(sc, R92C_WMAC_TRXPTCL_CTL, 0x180, 0);
	rtwn_write_1(sc, R12A_DATA_SEC, R12A_DATA_SEC_NO_EXT);

	rtwn_bb_setbits(sc, R92C_FPGA0_RFMOD, R92C_RFMOD_40MHZ, 0);
	rtwn_bb_setbits(sc, R92C_FPGA1_RFMOD, R92C_RFMOD_40MHZ, 0);

	/* Select 20MHz bandwidth. */
	for (i = 0; i < sc->nrxchains; i++)
		rtwn_rf_setbits(sc, i, R92C_RF_CHNLBW,
		    R88E_RF_CHNLBW_BW20, 0xc00);

	rtwn_bb_setbits(sc, R92C_OFDM0_TXPSEUDONOISEWGT, 0xc0000000, 0);
}