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
struct rtwn_softc {int nrxchains; int /*<<< orphan*/ * rf_prog; struct r92c_softc* sc_priv; } ;
struct r92c_softc {int chip; int /*<<< orphan*/ * rf_chnlbw; } ;

/* Variables and functions */
 int R92C_CHIP_92C ; 
 int R92C_CHIP_UMC_A_CUT ; 
 int /*<<< orphan*/  R92C_FPGA0_RFIFACEOE (int) ; 
 int /*<<< orphan*/  R92C_FPGA0_RFIFACESW (int) ; 
 int /*<<< orphan*/  R92C_FPGA0_RFMOD ; 
 int /*<<< orphan*/  R92C_HSSI_PARAM2 (int) ; 
 int R92C_HSSI_PARAM2_ADDR_LENGTH ; 
 int R92C_HSSI_PARAM2_DATA_LENGTH ; 
 int R92C_RFMOD_CCK_EN ; 
 int R92C_RFMOD_OFDM_EN ; 
 int /*<<< orphan*/  R92C_RF_CHNLBW ; 
 int /*<<< orphan*/  R92C_RF_RX_G1 ; 
 int /*<<< orphan*/  R92C_RF_RX_G2 ; 
 scalar_t__ r92c_init_rf_chain (struct rtwn_softc*,int /*<<< orphan*/ *,int) ; 
 int rtwn_bb_read (struct rtwn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_bb_setbits (struct rtwn_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtwn_delay (struct rtwn_softc*,int) ; 
 int /*<<< orphan*/  rtwn_rf_read (struct rtwn_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_rf_write (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
r92c_init_rf(struct rtwn_softc *sc)
{
	struct r92c_softc *rs = sc->sc_priv;
	uint32_t reg, type;
	int i, chain, idx, off;

	for (chain = 0, i = 0; chain < sc->nrxchains; chain++, i++) {
		/* Save RF_ENV control type. */
		idx = chain / 2;
		off = (chain % 2) * 16;
		reg = rtwn_bb_read(sc, R92C_FPGA0_RFIFACESW(idx));
		type = (reg >> off) & 0x10;

		/* Set RF_ENV enable. */
		rtwn_bb_setbits(sc, R92C_FPGA0_RFIFACEOE(chain),
		    0, 0x100000);
		rtwn_delay(sc, 1);
		/* Set RF_ENV output high. */
		rtwn_bb_setbits(sc, R92C_FPGA0_RFIFACEOE(chain),
		    0, 0x10);
		rtwn_delay(sc, 1);
		/* Set address and data lengths of RF registers. */
		rtwn_bb_setbits(sc, R92C_HSSI_PARAM2(chain),
		    R92C_HSSI_PARAM2_ADDR_LENGTH, 0);
		rtwn_delay(sc, 1);
		rtwn_bb_setbits(sc, R92C_HSSI_PARAM2(chain),
		    R92C_HSSI_PARAM2_DATA_LENGTH, 0);
		rtwn_delay(sc, 1);

		/* Write RF initialization values for this chain. */
		i += r92c_init_rf_chain(sc, &sc->rf_prog[i], chain);

		/* Restore RF_ENV control type. */
		rtwn_bb_setbits(sc, R92C_FPGA0_RFIFACESW(idx),
		    0x10 << off, type << off);

		/* Cache RF register CHNLBW. */
		rs->rf_chnlbw[chain] = rtwn_rf_read(sc, chain,
		    R92C_RF_CHNLBW);
	}

	if ((rs->chip & (R92C_CHIP_UMC_A_CUT | R92C_CHIP_92C)) ==
	    R92C_CHIP_UMC_A_CUT) {
		rtwn_rf_write(sc, 0, R92C_RF_RX_G1, 0x30255);
		rtwn_rf_write(sc, 0, R92C_RF_RX_G2, 0x50a00);
	}

	/* Turn CCK and OFDM blocks on. */
	rtwn_bb_setbits(sc, R92C_FPGA0_RFMOD, 0, R92C_RFMOD_CCK_EN);
	rtwn_bb_setbits(sc, R92C_FPGA0_RFMOD, 0, R92C_RFMOD_OFDM_EN);
}