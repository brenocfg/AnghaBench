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
typedef  scalar_t__ usb_error_t ;
typedef  int uint8_t ;
struct urtw_softc {int* sc_txpwr_cck; int* sc_txpwr_ofdm; int /*<<< orphan*/  sc_mtx; scalar_t__ sc_txpwr_ofdm_base; scalar_t__ sc_txpwr_cck_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_8225_ANAPARAM2_ON ; 
 int /*<<< orphan*/  URTW_TX_GAIN_CCK ; 
 int /*<<< orphan*/  URTW_TX_GAIN_OFDM ; 
 scalar_t__ urtw_8185_set_anaparam2 (struct urtw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urtw_8187_write_phy_cck (struct urtw_softc*,int,int) ; 
 int /*<<< orphan*/  urtw_8187_write_phy_ofdm (struct urtw_softc*,int,int) ; 
 int /*<<< orphan*/ * urtw_8225v2_tx_gain_cck_ofdm ; 
 int* urtw_8225v2_txpwr_cck ; 
 int* urtw_8225v2_txpwr_cck_ch14 ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static usb_error_t
urtw_8225v2_set_txpwrlvl(struct urtw_softc *sc, int chan)
{
	int i;
	uint8_t *cck_pwrtable;
	uint8_t cck_pwrlvl_max = 15, ofdm_pwrlvl_max = 25, ofdm_pwrlvl_min = 10;
	uint8_t cck_pwrlvl = sc->sc_txpwr_cck[chan] & 0xff;
	uint8_t ofdm_pwrlvl = sc->sc_txpwr_ofdm[chan] & 0xff;
	usb_error_t error;

	/* CCK power setting */
	cck_pwrlvl = (cck_pwrlvl > cck_pwrlvl_max) ? cck_pwrlvl_max : cck_pwrlvl;
	cck_pwrlvl += sc->sc_txpwr_cck_base;
	cck_pwrlvl = (cck_pwrlvl > 35) ? 35 : cck_pwrlvl;
	cck_pwrtable = (chan == 14) ? urtw_8225v2_txpwr_cck_ch14 :
	    urtw_8225v2_txpwr_cck;

	for (i = 0; i < 8; i++)
		urtw_8187_write_phy_cck(sc, 0x44 + i, cck_pwrtable[i]);

	urtw_write8_m(sc, URTW_TX_GAIN_CCK,
	    urtw_8225v2_tx_gain_cck_ofdm[cck_pwrlvl]);
	usb_pause_mtx(&sc->sc_mtx, 1);

	/* OFDM power setting */
	ofdm_pwrlvl = (ofdm_pwrlvl > (ofdm_pwrlvl_max - ofdm_pwrlvl_min)) ?
		ofdm_pwrlvl_max : ofdm_pwrlvl + ofdm_pwrlvl_min;
	ofdm_pwrlvl += sc->sc_txpwr_ofdm_base;
	ofdm_pwrlvl = (ofdm_pwrlvl > 35) ? 35 : ofdm_pwrlvl;

	error = urtw_8185_set_anaparam2(sc, URTW_8225_ANAPARAM2_ON);
	if (error)
		goto fail;

	urtw_8187_write_phy_ofdm(sc, 2, 0x42);
	urtw_8187_write_phy_ofdm(sc, 5, 0x0);
	urtw_8187_write_phy_ofdm(sc, 6, 0x40);
	urtw_8187_write_phy_ofdm(sc, 7, 0x0);
	urtw_8187_write_phy_ofdm(sc, 8, 0x40);

	urtw_write8_m(sc, URTW_TX_GAIN_OFDM,
	    urtw_8225v2_tx_gain_cck_ofdm[ofdm_pwrlvl]);
	usb_pause_mtx(&sc->sc_mtx, 1);
fail:
	return (error);
}