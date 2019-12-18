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
typedef  scalar_t__ uint16_t ;
struct wpi_softc {int dummy; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel*) ; 
 scalar_t__ WPI_PASSIVE_DWELL_BASE ; 
 scalar_t__ WPI_PASSIVE_DWELL_TIME_2GHZ ; 
 scalar_t__ WPI_PASSIVE_DWELL_TIME_5GHZ ; 
 scalar_t__ wpi_limit_dwell (struct wpi_softc*,scalar_t__) ; 

__attribute__((used)) static uint16_t
wpi_get_passive_dwell_time(struct wpi_softc *sc, struct ieee80211_channel *c)
{
	uint16_t passive;

	if (c == NULL || IEEE80211_IS_CHAN_2GHZ(c))
		passive = WPI_PASSIVE_DWELL_BASE + WPI_PASSIVE_DWELL_TIME_2GHZ;
	else
		passive = WPI_PASSIVE_DWELL_BASE + WPI_PASSIVE_DWELL_TIME_5GHZ;

	/* Clamp to the beacon interval if we're associated. */
	return (wpi_limit_dwell(sc, passive));
}