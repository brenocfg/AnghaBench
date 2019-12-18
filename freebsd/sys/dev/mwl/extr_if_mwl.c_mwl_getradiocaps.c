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
struct mwl_softc {int dummy; } ;
struct ieee80211com {struct mwl_softc* ic_softc; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  getchannels (struct mwl_softc*,int,int*,struct ieee80211_channel*) ; 

__attribute__((used)) static void
mwl_getradiocaps(struct ieee80211com *ic,
	int maxchans, int *nchans, struct ieee80211_channel chans[])
{
	struct mwl_softc *sc = ic->ic_softc;

	getchannels(sc, maxchans, nchans, chans);
}