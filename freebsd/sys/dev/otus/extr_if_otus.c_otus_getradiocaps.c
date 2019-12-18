#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int opCapFlags; } ;
struct TYPE_4__ {TYPE_1__ baseEepHeader; } ;
struct otus_softc {TYPE_2__ eeprom; scalar_t__ sc_ht; } ;
struct ieee80211com {struct otus_softc* ic_softc; } ;
struct ieee80211_channel {int dummy; } ;
typedef  int /*<<< orphan*/  bands ;

/* Variables and functions */
 int AR5416_OPFLAGS_11A ; 
 int AR5416_OPFLAGS_11G ; 
 int /*<<< orphan*/  IEEE80211_MODE_11A ; 
 int /*<<< orphan*/  IEEE80211_MODE_11B ; 
 int /*<<< orphan*/  IEEE80211_MODE_11G ; 
 int /*<<< orphan*/  IEEE80211_MODE_11NG ; 
 int IEEE80211_MODE_BYTES ; 
 int /*<<< orphan*/ * ar_chans ; 
 int /*<<< orphan*/  ieee80211_add_channel_list_2ghz (struct ieee80211_channel*,int,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_add_channel_list_5ghz (struct ieee80211_channel*,int,int*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
otus_getradiocaps(struct ieee80211com *ic,
    int maxchans, int *nchans, struct ieee80211_channel chans[])
{
	struct otus_softc *sc = ic->ic_softc;
	uint8_t bands[IEEE80211_MODE_BYTES];

	/* Set supported .11b and .11g rates. */
	memset(bands, 0, sizeof(bands));
	if (sc->eeprom.baseEepHeader.opCapFlags & AR5416_OPFLAGS_11G) {
		setbit(bands, IEEE80211_MODE_11B);
		setbit(bands, IEEE80211_MODE_11G);
#if 0
		if (sc->sc_ht)
			setbit(bands, IEEE80211_MODE_11NG);
#endif
		ieee80211_add_channel_list_2ghz(chans, maxchans, nchans,
		    ar_chans, 14, bands, 0);
	}
	if (sc->eeprom.baseEepHeader.opCapFlags & AR5416_OPFLAGS_11A) {
		setbit(bands, IEEE80211_MODE_11A);
		ieee80211_add_channel_list_5ghz(chans, maxchans, nchans,
                    &ar_chans[14], nitems(ar_chans) - 14, bands, 0);
	}
}