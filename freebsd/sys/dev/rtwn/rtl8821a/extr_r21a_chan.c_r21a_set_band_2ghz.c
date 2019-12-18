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
struct rtwn_softc {struct r12a_softc* sc_priv; } ;
struct r12a_softc {scalar_t__ ext_lna_2g; } ;

/* Variables and functions */
 int /*<<< orphan*/  R12A_CCK_CHECK ; 
 int /*<<< orphan*/  R12A_CCK_RX_PATH ; 
 int /*<<< orphan*/  R12A_OFDMCCK_EN ; 
 int R12A_OFDMCCK_EN_CCK ; 
 int R12A_OFDMCCK_EN_OFDM ; 
 int /*<<< orphan*/  R12A_RFE_INV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R12A_RFE_PINMUX (int /*<<< orphan*/ ) ; 
 int R12A_RFE_PINMUX_LNA_MASK ; 
 int R12A_RFE_PINMUX_PA_A_MASK ; 
 int /*<<< orphan*/  R12A_TX_PATH ; 
 int /*<<< orphan*/  R12A_TX_SCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r21a_bypass_ext_lna_2ghz (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_bb_setbits (struct rtwn_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtwn_set_basicrates (struct rtwn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
r21a_set_band_2ghz(struct rtwn_softc *sc, uint32_t basicrates)
{
	struct r12a_softc *rs = sc->sc_priv;

	/* Enable CCK / OFDM. */
	rtwn_bb_setbits(sc, R12A_OFDMCCK_EN,
	    0, R12A_OFDMCCK_EN_CCK | R12A_OFDMCCK_EN_OFDM);

	/* Turn off RF PA and LNA. */
	rtwn_bb_setbits(sc, R12A_RFE_PINMUX(0),
	    R12A_RFE_PINMUX_LNA_MASK, 0x7000);
	rtwn_bb_setbits(sc, R12A_RFE_PINMUX(0),
	    R12A_RFE_PINMUX_PA_A_MASK, 0x70);

	if (rs->ext_lna_2g) {
		/* Turn on 2.4 GHz external LNA. */
		rtwn_bb_setbits(sc, R12A_RFE_INV(0), 0, 0x00100000);
		rtwn_bb_setbits(sc, R12A_RFE_INV(0), 0x00400000, 0);
		rtwn_bb_setbits(sc, R12A_RFE_PINMUX(0), 0x05, 0x02);
		rtwn_bb_setbits(sc, R12A_RFE_PINMUX(0), 0x0500, 0x0200);
	} else {
		/* Bypass 2.4 GHz external LNA. */
		r21a_bypass_ext_lna_2ghz(sc);
	}

	/* Select AGC table. */
	rtwn_bb_setbits(sc, R12A_TX_SCALE(0), 0x0f00, 0);

	rtwn_bb_setbits(sc, R12A_TX_PATH, 0xf0, 0x10);
	rtwn_bb_setbits(sc, R12A_CCK_RX_PATH, 0x0f000000, 0x01000000);

	/* Write basic rates. */
	rtwn_set_basicrates(sc, basicrates);

	rtwn_write_1(sc, R12A_CCK_CHECK, 0);
}