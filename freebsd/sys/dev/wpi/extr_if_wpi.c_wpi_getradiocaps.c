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
struct wpi_softc {int dummy; } ;
struct ieee80211com {struct wpi_softc* ic_softc; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int WPI_CHAN_BANDS_COUNT ; 
 int /*<<< orphan*/  wpi_read_eeprom_band (struct wpi_softc*,int,int,int*,struct ieee80211_channel*) ; 

__attribute__((used)) static void
wpi_getradiocaps(struct ieee80211com *ic,
    int maxchans, int *nchans, struct ieee80211_channel chans[])
{
	struct wpi_softc *sc = ic->ic_softc;
	int i;

	/* Parse the list of authorized channels. */
	for (i = 0; i < WPI_CHAN_BANDS_COUNT && *nchans < maxchans; i++)
		wpi_read_eeprom_band(sc, i, maxchans, nchans, chans);
}