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
struct urtw_softc {int /*<<< orphan*/  sc_mtx; } ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  urtw_8187_write_phy_ofdm (struct urtw_softc*,int,int) ; 
 int* urtw_8225v2_gain_bg ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static usb_error_t
urtw_8225v2_setgain(struct urtw_softc *sc, int16_t gain)
{
	uint8_t *gainp;
	usb_error_t error;

	/* XXX for A?  */
	gainp = urtw_8225v2_gain_bg;
	urtw_8187_write_phy_ofdm(sc, 0x0d, gainp[gain * 3]);
	usb_pause_mtx(&sc->sc_mtx, 1);
	urtw_8187_write_phy_ofdm(sc, 0x1b, gainp[gain * 3 + 1]);
	usb_pause_mtx(&sc->sc_mtx, 1);
	urtw_8187_write_phy_ofdm(sc, 0x1d, gainp[gain * 3 + 2]);
	usb_pause_mtx(&sc->sc_mtx, 1);
	urtw_8187_write_phy_ofdm(sc, 0x21, 0x17);
	usb_pause_mtx(&sc->sc_mtx, 1);
fail:
	return (error);
}