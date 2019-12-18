#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpi_softc {struct wpi_eeprom_chan** eeprom_channels; } ;
struct wpi_eeprom_chan {int dummy; } ;
struct ieee80211_channel {scalar_t__ ic_ieee; } ;
struct TYPE_2__ {int nchan; scalar_t__* chan; } ;

/* Variables and functions */
 int IEEE80211_IS_CHAN_A (struct ieee80211_channel*) ; 
 int WPI_CHAN_BANDS_COUNT ; 
 TYPE_1__* wpi_bands ; 

__attribute__((used)) static struct wpi_eeprom_chan *
wpi_find_eeprom_channel(struct wpi_softc *sc, struct ieee80211_channel *c)
{
	int i, j;

	for (j = 0; j < WPI_CHAN_BANDS_COUNT; j++)
		for (i = 0; i < wpi_bands[j].nchan; i++)
			if (wpi_bands[j].chan[i] == c->ic_ieee &&
			    ((j == 0) ^ IEEE80211_IS_CHAN_A(c)) == 1)
				return &sc->eeprom_channels[j][i];

	return NULL;
}