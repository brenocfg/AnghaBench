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
typedef  int uint32_t ;
struct ieee80211com {scalar_t__ ic_opmode; scalar_t__ ic_promisc; scalar_t__ ic_allmulti; } ;
struct urtw_softc {int sc_flags; int sc_crcmon; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_MONITOR ; 
 int URTW_MAX_RX_DMA_2048 ; 
 int URTW_MAX_RX_DMA_MASK ; 
 int URTW_RCR_ONLYERLPKT ; 
 int URTW_RTL8187B ; 
 int /*<<< orphan*/  URTW_RX ; 
 int URTW_RX_AUTORESETPHY ; 
 int URTW_RX_CHECK_BSSID ; 
 int URTW_RX_FIFO_THRESHOLD_MASK ; 
 int URTW_RX_FIFO_THRESHOLD_NONE ; 
 int URTW_RX_FILTER_ALLMAC ; 
 int URTW_RX_FILTER_BCAST ; 
 int URTW_RX_FILTER_CRCERR ; 
 int URTW_RX_FILTER_CTL ; 
 int URTW_RX_FILTER_DATA ; 
 int URTW_RX_FILTER_ICVERR ; 
 int URTW_RX_FILTER_MASK ; 
 int URTW_RX_FILTER_MCAST ; 
 int URTW_RX_FILTER_MNG ; 
 int URTW_RX_FILTER_NICMAC ; 
 int URTW_RX_FILTER_PWR ; 
 int /*<<< orphan*/  urtw_read32_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  urtw_write32_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static usb_error_t
urtw_rx_setconf(struct urtw_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint32_t data;
	usb_error_t error;

	urtw_read32_m(sc, URTW_RX, &data);
	data = data &~ URTW_RX_FILTER_MASK;
	if (sc->sc_flags & URTW_RTL8187B) {
		data = data | URTW_RX_FILTER_MNG | URTW_RX_FILTER_DATA |
		    URTW_RX_FILTER_MCAST | URTW_RX_FILTER_BCAST |
		    URTW_RX_FIFO_THRESHOLD_NONE |
		    URTW_MAX_RX_DMA_2048 |
		    URTW_RX_AUTORESETPHY | URTW_RCR_ONLYERLPKT;
	} else {
		data = data | URTW_RX_FILTER_MNG | URTW_RX_FILTER_DATA;
		data = data | URTW_RX_FILTER_BCAST | URTW_RX_FILTER_MCAST;

		if (ic->ic_opmode == IEEE80211_M_MONITOR) {
			data = data | URTW_RX_FILTER_ICVERR;
			data = data | URTW_RX_FILTER_PWR;
		}
		if (sc->sc_crcmon == 1 && ic->ic_opmode == IEEE80211_M_MONITOR)
			data = data | URTW_RX_FILTER_CRCERR;

		data = data &~ URTW_RX_FIFO_THRESHOLD_MASK;
		data = data | URTW_RX_FIFO_THRESHOLD_NONE |
		    URTW_RX_AUTORESETPHY;
		data = data &~ URTW_MAX_RX_DMA_MASK;
		data = data | URTW_MAX_RX_DMA_2048 | URTW_RCR_ONLYERLPKT;
	}

	/* XXX allmulti should not be checked here... */
	if (ic->ic_opmode == IEEE80211_M_MONITOR ||
	    ic->ic_promisc > 0 || ic->ic_allmulti > 0) {
		data = data | URTW_RX_FILTER_CTL;
		data = data | URTW_RX_FILTER_ALLMAC;
	} else {
		data = data | URTW_RX_FILTER_NICMAC;
		data = data | URTW_RX_CHECK_BSSID;
	}

	urtw_write32_m(sc, URTW_RX, data);
fail:
	return (error);
}