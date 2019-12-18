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
struct iwn_softc {int dummy; } ;
struct ieee80211com {struct iwn_softc* ic_softc; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int IWN_NBANDS ; 
 int /*<<< orphan*/  iwn_read_eeprom_band (struct iwn_softc*,int,int,int*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  iwn_read_eeprom_ht40 (struct iwn_softc*,int,int,int*,struct ieee80211_channel*) ; 

__attribute__((used)) static void
iwn_getradiocaps(struct ieee80211com *ic,
    int maxchans, int *nchans, struct ieee80211_channel chans[])
{
	struct iwn_softc *sc = ic->ic_softc;
	int i;

	/* Parse the list of authorized channels. */
	for (i = 0; i < 5 && *nchans < maxchans; i++)
		iwn_read_eeprom_band(sc, i, maxchans, nchans, chans);
	for (i = 5; i < IWN_NBANDS - 1 && *nchans < maxchans; i++)
		iwn_read_eeprom_ht40(sc, i, maxchans, nchans, chans);
}