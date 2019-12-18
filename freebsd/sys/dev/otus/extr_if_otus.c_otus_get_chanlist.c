#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int opCapFlags; int /*<<< orphan*/ * regDmn; } ;
struct TYPE_5__ {TYPE_1__ baseEepHeader; } ;
struct ieee80211com {TYPE_3__* ic_channels; } ;
struct otus_softc {TYPE_2__ eeprom; struct ieee80211com sc_ic; } ;
struct TYPE_6__ {int ic_flags; void* ic_freq; } ;

/* Variables and functions */
 int AR5416_OPFLAGS_11A ; 
 int AR5416_OPFLAGS_11G ; 
 int IEEE80211_CHAN_2GHZ ; 
 int IEEE80211_CHAN_5GHZ ; 
 int IEEE80211_CHAN_A ; 
 int IEEE80211_CHAN_CCK ; 
 int IEEE80211_CHAN_DYN ; 
 int IEEE80211_CHAN_OFDM ; 
 int /*<<< orphan*/  OTUS_DEBUG_RESET ; 
 int /*<<< orphan*/  OTUS_DPRINTF (struct otus_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 size_t* ar_chans ; 
 void* ieee80211_ieee2mhz (size_t,int) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int nitems (size_t*) ; 

void
otus_get_chanlist(struct otus_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint16_t domain;
	uint8_t chan;
	int i;

	/* XXX regulatory domain. */
	domain = le16toh(sc->eeprom.baseEepHeader.regDmn[0]);
	OTUS_DPRINTF(sc, OTUS_DEBUG_RESET, "regdomain=0x%04x\n", domain);

	if (sc->eeprom.baseEepHeader.opCapFlags & AR5416_OPFLAGS_11G) {
		for (i = 0; i < 14; i++) {
			chan = ar_chans[i];
			ic->ic_channels[chan].ic_freq =
			    ieee80211_ieee2mhz(chan, IEEE80211_CHAN_2GHZ);
			ic->ic_channels[chan].ic_flags =
			    IEEE80211_CHAN_CCK | IEEE80211_CHAN_OFDM |
			    IEEE80211_CHAN_DYN | IEEE80211_CHAN_2GHZ;
		}
	}
	if (sc->eeprom.baseEepHeader.opCapFlags & AR5416_OPFLAGS_11A) {
		for (i = 14; i < nitems(ar_chans); i++) {
			chan = ar_chans[i];
			ic->ic_channels[chan].ic_freq =
			    ieee80211_ieee2mhz(chan, IEEE80211_CHAN_5GHZ);
			ic->ic_channels[chan].ic_flags = IEEE80211_CHAN_A;
		}
	}
}