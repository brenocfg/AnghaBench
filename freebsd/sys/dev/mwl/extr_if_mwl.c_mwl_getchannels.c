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
struct TYPE_2__ {char location; char* isocc; int /*<<< orphan*/  country; int /*<<< orphan*/  regdomain; } ;
struct ieee80211com {scalar_t__ ic_nchans; TYPE_1__ ic_regdomain; int /*<<< orphan*/  ic_channels; } ;
struct mwl_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRY_DEFAULT ; 
 int EIO ; 
 int /*<<< orphan*/  IEEE80211_CHAN_MAX ; 
 int /*<<< orphan*/  SKU_DEBUG ; 
 int /*<<< orphan*/  getchannels (struct mwl_softc*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mwl_getchannels(struct mwl_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;

	/*
	 * Use the channel info from the hal to craft the
	 * channel list for net80211.  Note that we pass up
	 * an unsorted list; net80211 will sort it for us.
	 */
	memset(ic->ic_channels, 0, sizeof(ic->ic_channels));
	ic->ic_nchans = 0;
	getchannels(sc, IEEE80211_CHAN_MAX, &ic->ic_nchans, ic->ic_channels);

	ic->ic_regdomain.regdomain = SKU_DEBUG;
	ic->ic_regdomain.country = CTRY_DEFAULT;
	ic->ic_regdomain.location = 'I';
	ic->ic_regdomain.isocc[0] = ' ';	/* XXX? */
	ic->ic_regdomain.isocc[1] = ' ';
	return (ic->ic_nchans == 0 ? EIO : 0);
}