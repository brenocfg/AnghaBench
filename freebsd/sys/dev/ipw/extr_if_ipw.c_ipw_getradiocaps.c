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
typedef  int /*<<< orphan*/  uint8_t ;
struct ipw_softc {int chanmask; } ;
struct ieee80211com {struct ipw_softc* ic_softc; } ;
struct ieee80211_channel {int dummy; } ;
typedef  int /*<<< orphan*/  bands ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MODE_11B ; 
 int IEEE80211_MODE_BYTES ; 
 int /*<<< orphan*/  ieee80211_add_channel (struct ieee80211_channel*,int,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipw_getradiocaps(struct ieee80211com *ic,
    int maxchans, int *nchans, struct ieee80211_channel chans[])
{
	struct ipw_softc *sc = ic->ic_softc;
	uint8_t bands[IEEE80211_MODE_BYTES];
	int i;

	memset(bands, 0, sizeof(bands));
	setbit(bands, IEEE80211_MODE_11B);

	for (i = 1; i < 16; i++) {
		if (sc->chanmask & (1 << i)) {
			ieee80211_add_channel(chans, maxchans, nchans,
			    i, 0, 0, 0, bands);
		}
	}

}