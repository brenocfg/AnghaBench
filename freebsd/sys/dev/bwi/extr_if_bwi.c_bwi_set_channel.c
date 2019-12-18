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
struct ieee80211com {struct ieee80211_channel* ic_curchan; struct bwi_softc* ic_softc; } ;
struct ieee80211_channel {int dummy; } ;
struct bwi_softc {int /*<<< orphan*/  sc_rates; TYPE_1__* sc_cur_regwin; } ;
struct bwi_mac {int dummy; } ;
struct TYPE_2__ {scalar_t__ rw_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_LOCK (struct bwi_softc*) ; 
 scalar_t__ BWI_REGWIN_T_MAC ; 
 int /*<<< orphan*/  BWI_UNLOCK (struct bwi_softc*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bwi_rf_set_chan (struct bwi_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_chan2ieee (struct ieee80211com*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  ieee80211_get_ratetable (struct ieee80211_channel*) ; 

__attribute__((used)) static void
bwi_set_channel(struct ieee80211com *ic)
{
	struct bwi_softc *sc = ic->ic_softc;
	struct ieee80211_channel *c = ic->ic_curchan;
	struct bwi_mac *mac;

	BWI_LOCK(sc);
	KASSERT(sc->sc_cur_regwin->rw_type == BWI_REGWIN_T_MAC,
	    ("current regwin type %d", sc->sc_cur_regwin->rw_type));
	mac = (struct bwi_mac *)sc->sc_cur_regwin;
	bwi_rf_set_chan(mac, ieee80211_chan2ieee(ic, c), 0);

	sc->sc_rates = ieee80211_get_ratetable(c);
	BWI_UNLOCK(sc);
}