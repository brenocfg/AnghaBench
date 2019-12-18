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
typedef  int /*<<< orphan*/  u_long ;
struct mwl_softc {int /*<<< orphan*/  sc_imask; struct mwl_hal* sc_mh; } ;
struct mwl_hal_vap {int dummy; } ;
struct mwl_hal {int dummy; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_state; struct ieee80211com* iv_ic; } ;
struct ieee80211com {struct mwl_softc* ic_softc; } ;
struct TYPE_2__ {struct mwl_hal_vap* mv_hvap; } ;

/* Variables and functions */
 TYPE_1__* MWL_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  mwl_hal_intrset (struct mwl_hal*,int /*<<< orphan*/ ) ; 
 int mwl_reset_vap (struct ieee80211vap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mwl_reset(struct ieee80211vap *vap, u_long cmd)
{
	struct mwl_hal_vap *hvap = MWL_VAP(vap)->mv_hvap;
	int error = 0;

	if (hvap != NULL) {			/* WDS, MONITOR, etc. */
		struct ieee80211com *ic = vap->iv_ic;
		struct mwl_softc *sc = ic->ic_softc;
		struct mwl_hal *mh = sc->sc_mh;

		/* XXX handle DWDS sta vap change */
		/* XXX do we need to disable interrupts? */
		mwl_hal_intrset(mh, 0);		/* disable interrupts */
		error = mwl_reset_vap(vap, vap->iv_state);
		mwl_hal_intrset(mh, sc->sc_imask);
	}
	return error;
}