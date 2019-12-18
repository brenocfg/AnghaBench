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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint8_t ;
struct urtw_softc {int* sc_txpwr_cck; int* sc_txpwr_ofdm; int sc_flags; int /*<<< orphan*/  sc_mtx; scalar_t__ sc_txpwr_ofdm_base; scalar_t__ sc_txpwr_cck_base; } ;

/* Variables and functions */
 int URTW_RTL8187B_REV_B ; 
 int /*<<< orphan*/  URTW_TX_GAIN_CCK ; 
 int /*<<< orphan*/  URTW_TX_GAIN_OFDM ; 
 int /*<<< orphan*/  urtw_8187_write_phy_cck (struct urtw_softc*,int,int) ; 
 int /*<<< orphan*/  urtw_8187_write_phy_ofdm (struct urtw_softc*,int,int) ; 
 int* urtw_8225v2_tx_gain_cck_ofdm ; 
 int* urtw_8225v2b_txpwr_cck ; 
 int* urtw_8225v2b_txpwr_cck_ch14 ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static usb_error_t
urtw_8225v2b_set_txpwrlvl(struct urtw_softc *sc, int chan)
{
	int i;
	uint8_t *cck_pwrtable;
	uint8_t cck_pwrlvl_max = 15;
	uint8_t cck_pwrlvl = sc->sc_txpwr_cck[chan] & 0xff;
	uint8_t ofdm_pwrlvl = sc->sc_txpwr_ofdm[chan] & 0xff;
	usb_error_t error;

	/* CCK power setting */
	cck_pwrlvl = (cck_pwrlvl > cck_pwrlvl_max) ?
	    ((sc->sc_flags & URTW_RTL8187B_REV_B) ? cck_pwrlvl_max : 22) :
	    (cck_pwrlvl + ((sc->sc_flags & URTW_RTL8187B_REV_B) ? 0 : 7));
	cck_pwrlvl += sc->sc_txpwr_cck_base;
	cck_pwrlvl = (cck_pwrlvl > 35) ? 35 : cck_pwrlvl;
	cck_pwrtable = (chan == 14) ? urtw_8225v2b_txpwr_cck_ch14 :
	    urtw_8225v2b_txpwr_cck;

	if (sc->sc_flags & URTW_RTL8187B_REV_B)
		cck_pwrtable += (cck_pwrlvl <= 6) ? 0 :
		    ((cck_pwrlvl <= 11) ? 8 : 16);
	else
		cck_pwrtable += (cck_pwrlvl <= 5) ? 0 :
		    ((cck_pwrlvl <= 11) ? 8 : ((cck_pwrlvl <= 17) ? 16 : 24));

	for (i = 0; i < 8; i++)
		urtw_8187_write_phy_cck(sc, 0x44 + i, cck_pwrtable[i]);

	urtw_write8_m(sc, URTW_TX_GAIN_CCK,
	    urtw_8225v2_tx_gain_cck_ofdm[cck_pwrlvl] << 1);
	usb_pause_mtx(&sc->sc_mtx, 1);

	/* OFDM power setting */
	ofdm_pwrlvl = (ofdm_pwrlvl > 15) ?
	    ((sc->sc_flags & URTW_RTL8187B_REV_B) ? 17 : 25) :
	    (ofdm_pwrlvl + ((sc->sc_flags & URTW_RTL8187B_REV_B) ? 2 : 10));
	ofdm_pwrlvl += sc->sc_txpwr_ofdm_base;
	ofdm_pwrlvl = (ofdm_pwrlvl > 35) ? 35 : ofdm_pwrlvl;

	urtw_write8_m(sc, URTW_TX_GAIN_OFDM,
	    urtw_8225v2_tx_gain_cck_ofdm[ofdm_pwrlvl] << 1);

	if (sc->sc_flags & URTW_RTL8187B_REV_B) {
		if (ofdm_pwrlvl <= 11) {
			urtw_8187_write_phy_ofdm(sc, 0x87, 0x60);
			urtw_8187_write_phy_ofdm(sc, 0x89, 0x60);
		} else {
			urtw_8187_write_phy_ofdm(sc, 0x87, 0x5c);
			urtw_8187_write_phy_ofdm(sc, 0x89, 0x5c);
		}
	} else {
		if (ofdm_pwrlvl <= 11) {
			urtw_8187_write_phy_ofdm(sc, 0x87, 0x5c);
			urtw_8187_write_phy_ofdm(sc, 0x89, 0x5c);
		} else if (ofdm_pwrlvl <= 17) {
			urtw_8187_write_phy_ofdm(sc, 0x87, 0x54);
			urtw_8187_write_phy_ofdm(sc, 0x89, 0x54);
		} else {
			urtw_8187_write_phy_ofdm(sc, 0x87, 0x50);
			urtw_8187_write_phy_ofdm(sc, 0x89, 0x50);
		}
	}
	usb_pause_mtx(&sc->sc_mtx, 1);
fail:
	return (error);
}