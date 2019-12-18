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
struct wmeParams {int wmep_aifsn; int wmep_txopLimit; int /*<<< orphan*/  wmep_logcwmax; int /*<<< orphan*/  wmep_logcwmin; } ;
struct mwl_txq {int /*<<< orphan*/  qnum; } ;
struct ieee80211com {int dummy; } ;
struct mwl_softc {int /*<<< orphan*/  sc_dev; struct mwl_hal* sc_mh; struct mwl_txq** sc_ac2q; struct ieee80211com sc_ic; } ;
struct mwl_hal {int dummy; } ;
struct chanAccParams {struct wmeParams* cap_wmeParams; } ;

/* Variables and functions */
 int MWL_EXPONENT_TO_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ieee80211_wme_acnames ; 
 int /*<<< orphan*/  ieee80211_wme_ic_getparams (struct ieee80211com*,struct chanAccParams*) ; 
 scalar_t__ mwl_hal_setedcaparams (struct mwl_hal*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int
mwl_txq_update(struct mwl_softc *sc, int ac)
{
#define	MWL_EXPONENT_TO_VALUE(v)	((1<<v)-1)
	struct ieee80211com *ic = &sc->sc_ic;
	struct chanAccParams chp;
	struct mwl_txq *txq = sc->sc_ac2q[ac];
	struct wmeParams *wmep;
	struct mwl_hal *mh = sc->sc_mh;
	int aifs, cwmin, cwmax, txoplim;

	ieee80211_wme_ic_getparams(ic, &chp);
	wmep = &chp.cap_wmeParams[ac];

	aifs = wmep->wmep_aifsn;
	/* XXX in sta mode need to pass log values for cwmin/max */
	cwmin = MWL_EXPONENT_TO_VALUE(wmep->wmep_logcwmin);
	cwmax = MWL_EXPONENT_TO_VALUE(wmep->wmep_logcwmax);
	txoplim = wmep->wmep_txopLimit;		/* NB: units of 32us */

	if (mwl_hal_setedcaparams(mh, txq->qnum, cwmin, cwmax, aifs, txoplim)) {
		device_printf(sc->sc_dev, "unable to update hardware queue "
			"parameters for %s traffic!\n",
			ieee80211_wme_acnames[ac]);
		return 0;
	}
	return 1;
#undef MWL_EXPONENT_TO_VALUE
}