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
struct rtwn_softc {scalar_t__ sc_ratectl; scalar_t__ sc_tx_n_active; int sc_tx_timer; scalar_t__ qfullmsk; } ;
struct rtwn_usb_softc {int /*<<< orphan*/  uc_tx_pending; int /*<<< orphan*/  uc_tx_active; int /*<<< orphan*/  uc_tx_inactive; struct rtwn_softc uc_sc; } ;
struct rtwn_data {int /*<<< orphan*/ * m; int /*<<< orphan*/ * ni; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTWN_ASSERT_LOCKED (struct rtwn_softc*) ; 
 scalar_t__ RTWN_RATECTL_NET80211 ; 
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct rtwn_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_complete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static void
rtwn_usb_txeof(struct rtwn_usb_softc *uc, struct rtwn_data *data, int status)
{
	struct rtwn_softc *sc = &uc->uc_sc;

	RTWN_ASSERT_LOCKED(sc);

	if (data->ni != NULL)	/* not a beacon frame */
		ieee80211_tx_complete(data->ni, data->m, status);

	if (sc->sc_ratectl != RTWN_RATECTL_NET80211)
		if (sc->sc_tx_n_active > 0)
			sc->sc_tx_n_active--;

	data->ni = NULL;
	data->m = NULL;

	STAILQ_INSERT_TAIL(&uc->uc_tx_inactive, data, next);
	sc->qfullmsk = 0;
#ifndef D4054
	if (STAILQ_EMPTY(&uc->uc_tx_active) && STAILQ_EMPTY(&uc->uc_tx_pending))
		sc->sc_tx_timer = 0;
	else
		sc->sc_tx_timer = 5;
#endif
}