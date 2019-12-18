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
struct wmeParams {int /*<<< orphan*/  wmep_acm; int /*<<< orphan*/  wmep_txopLimit; int /*<<< orphan*/  wmep_logcwmax; int /*<<< orphan*/  wmep_logcwmin; int /*<<< orphan*/  wmep_aifsn; } ;
struct ieee80211com {int dummy; } ;
struct iwi_softc {TYPE_1__* wme; struct ieee80211com sc_ic; } ;
struct chanAccParams {struct wmeParams* cap_wmeParams; } ;
struct TYPE_2__ {int /*<<< orphan*/ * acm; int /*<<< orphan*/ * burst; void** cwmax; void** cwmin; int /*<<< orphan*/ * aifsn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  IWI_CMD_SET_WME_PARAMS ; 
 void* IWI_EXP2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWI_USEC (int /*<<< orphan*/ ) ; 
 int WME_NUM_AC ; 
 int /*<<< orphan*/  ieee80211_wme_ic_getparams (struct ieee80211com*,struct chanAccParams*) ; 
 int iwi_cmd (struct iwi_softc*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static int
iwi_wme_setparams(struct iwi_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct chanAccParams chp;
	const struct wmeParams *wmep;
	int ac;

	ieee80211_wme_ic_getparams(ic, &chp);

	for (ac = 0; ac < WME_NUM_AC; ac++) {
		/* set WME values for current operating mode */
		wmep = &chp.cap_wmeParams[ac];
		sc->wme[0].aifsn[ac] = wmep->wmep_aifsn;
		sc->wme[0].cwmin[ac] = IWI_EXP2(wmep->wmep_logcwmin);
		sc->wme[0].cwmax[ac] = IWI_EXP2(wmep->wmep_logcwmax);
		sc->wme[0].burst[ac] = IWI_USEC(wmep->wmep_txopLimit);
		sc->wme[0].acm[ac]   = wmep->wmep_acm;
	}

	DPRINTF(("Setting WME parameters\n"));
	return iwi_cmd(sc, IWI_CMD_SET_WME_PARAMS, sc->wme, sizeof sc->wme);
}