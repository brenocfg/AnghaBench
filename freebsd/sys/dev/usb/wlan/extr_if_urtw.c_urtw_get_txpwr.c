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
typedef  int uint32_t ;
struct urtw_softc {int sc_txpwr_cck_base; int sc_txpwr_ofdm_base; int* sc_txpwr_cck; int* sc_txpwr_ofdm; int sc_flags; } ;

/* Variables and functions */
 int URTW_EPROM_TXPW0 ; 
 int URTW_EPROM_TXPW1 ; 
 int URTW_EPROM_TXPW2 ; 
 int URTW_EPROM_TXPW_BASE ; 
 int URTW_RTL8187B ; 
 scalar_t__ urtw_eprom_read32 (struct urtw_softc*,int,int*) ; 

__attribute__((used)) static usb_error_t
urtw_get_txpwr(struct urtw_softc *sc)
{
	int i, j;
	uint32_t data;
	usb_error_t error;

	error = urtw_eprom_read32(sc, URTW_EPROM_TXPW_BASE, &data);
	if (error != 0)
		goto fail;
	sc->sc_txpwr_cck_base = data & 0xf;
	sc->sc_txpwr_ofdm_base = (data >> 4) & 0xf;

	for (i = 1, j = 0; i < 6; i += 2, j++) {
		error = urtw_eprom_read32(sc, URTW_EPROM_TXPW0 + j, &data);
		if (error != 0)
			goto fail;
		sc->sc_txpwr_cck[i] = data & 0xf;
		sc->sc_txpwr_cck[i + 1] = (data & 0xf00) >> 8;
		sc->sc_txpwr_ofdm[i] = (data & 0xf0) >> 4;
		sc->sc_txpwr_ofdm[i + 1] = (data & 0xf000) >> 12;
	}
	for (i = 1, j = 0; i < 4; i += 2, j++) {
		error = urtw_eprom_read32(sc, URTW_EPROM_TXPW1 + j, &data);
		if (error != 0)
			goto fail;
		sc->sc_txpwr_cck[i + 6] = data & 0xf;
		sc->sc_txpwr_cck[i + 6 + 1] = (data & 0xf00) >> 8;
		sc->sc_txpwr_ofdm[i + 6] = (data & 0xf0) >> 4;
		sc->sc_txpwr_ofdm[i + 6 + 1] = (data & 0xf000) >> 12;
	}
	if (sc->sc_flags & URTW_RTL8187B) {
		error = urtw_eprom_read32(sc, URTW_EPROM_TXPW2, &data);
		if (error != 0)
			goto fail;
		sc->sc_txpwr_cck[1 + 6 + 4] = data & 0xf;
		sc->sc_txpwr_ofdm[1 + 6 + 4] = (data & 0xf0) >> 4;
		error = urtw_eprom_read32(sc, 0x0a, &data);
		if (error != 0)
			goto fail;
		sc->sc_txpwr_cck[2 + 6 + 4] = data & 0xf;
		sc->sc_txpwr_ofdm[2 + 6 + 4] = (data & 0xf0) >> 4;
		error = urtw_eprom_read32(sc, 0x1c, &data);
		if (error != 0)
			goto fail;
		sc->sc_txpwr_cck[3 + 6 + 4] = data & 0xf;
		sc->sc_txpwr_cck[3 + 6 + 4 + 1] = (data & 0xf00) >> 8;
		sc->sc_txpwr_ofdm[3 + 6 + 4] = (data & 0xf0) >> 4;
		sc->sc_txpwr_ofdm[3 + 6 + 4 + 1] = (data & 0xf000) >> 12;
	} else {
		for (i = 1, j = 0; i < 4; i += 2, j++) {
			error = urtw_eprom_read32(sc, URTW_EPROM_TXPW2 + j,
			    &data);
			if (error != 0)
				goto fail;
			sc->sc_txpwr_cck[i + 6 + 4] = data & 0xf;
			sc->sc_txpwr_cck[i + 6 + 4 + 1] = (data & 0xf00) >> 8;
			sc->sc_txpwr_ofdm[i + 6 + 4] = (data & 0xf0) >> 4;
			sc->sc_txpwr_ofdm[i + 6 + 4 + 1] = (data & 0xf000) >> 12;
		}
	}
fail:
	return (error);
}