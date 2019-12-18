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
typedef  int u_int ;
struct ieee80211com {int dummy; } ;
struct rt2860_softc {int mac_ver; struct ieee80211com sc_ic; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int IEEE80211_CHAN_ANY ; 
 int ieee80211_chan2ieee (struct ieee80211com*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  rt2860_select_chan_group (struct rt2860_softc*,int) ; 
 int /*<<< orphan*/  rt2860_set_chan (struct rt2860_softc*,int) ; 
 int /*<<< orphan*/  rt3090_set_chan (struct rt2860_softc*,int) ; 
 int /*<<< orphan*/  rt5390_set_chan (struct rt2860_softc*,int) ; 

__attribute__((used)) static void
rt2860_switch_chan(struct rt2860_softc *sc, struct ieee80211_channel *c)
{
	struct ieee80211com *ic = &sc->sc_ic;
	u_int chan, group;

	chan = ieee80211_chan2ieee(ic, c);
	if (chan == 0 || chan == IEEE80211_CHAN_ANY)
		return;

	if (sc->mac_ver >= 0x5390)
		rt5390_set_chan(sc, chan);
	else if (sc->mac_ver >= 0x3071)
		rt3090_set_chan(sc, chan);
	else
		rt2860_set_chan(sc, chan);

	/* determine channel group */
	if (chan <= 14)
		group = 0;
	else if (chan <= 64)
		group = 1;
	else if (chan <= 128)
		group = 2;
	else
		group = 3;

	/* XXX necessary only when group has changed! */
	if (sc->mac_ver < 0x5390)
		rt2860_select_chan_group(sc, group);

	DELAY(1000);
}