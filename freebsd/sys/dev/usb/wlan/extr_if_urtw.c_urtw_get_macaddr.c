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
struct ieee80211com {int* ic_macaddr; } ;
struct urtw_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 scalar_t__ URTW_EPROM_MACADDR ; 
 scalar_t__ urtw_eprom_read32 (struct urtw_softc*,scalar_t__,int*) ; 

__attribute__((used)) static usb_error_t
urtw_get_macaddr(struct urtw_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t data;
	usb_error_t error;

	error = urtw_eprom_read32(sc, URTW_EPROM_MACADDR, &data);
	if (error != 0)
		goto fail;
	ic->ic_macaddr[0] = data & 0xff;
	ic->ic_macaddr[1] = (data & 0xff00) >> 8;
	error = urtw_eprom_read32(sc, URTW_EPROM_MACADDR + 1, &data);
	if (error != 0)
		goto fail;
	ic->ic_macaddr[2] = data & 0xff;
	ic->ic_macaddr[3] = (data & 0xff00) >> 8;
	error = urtw_eprom_read32(sc, URTW_EPROM_MACADDR + 2, &data);
	if (error != 0)
		goto fail;
	ic->ic_macaddr[4] = data & 0xff;
	ic->ic_macaddr[5] = (data & 0xff00) >> 8;
fail:
	return (error);
}