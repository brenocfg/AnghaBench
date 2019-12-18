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
struct iwi_softc {TYPE_1__* wme; } ;
struct TYPE_2__ {int /*<<< orphan*/ * acm; void** burst; void** cwmax; void** cwmin; int /*<<< orphan*/ * aifsn; } ;

/* Variables and functions */
 void* IWI_EXP2 (int /*<<< orphan*/ ) ; 
 void* IWI_USEC (int /*<<< orphan*/ ) ; 
 int WME_NUM_AC ; 
 struct wmeParams* iwi_wme_cck_params ; 
 struct wmeParams* iwi_wme_ofdm_params ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
iwi_wme_init(struct iwi_softc *sc)
{
	const struct wmeParams *wmep;
	int ac;

	memset(sc->wme, 0, sizeof sc->wme);
	for (ac = 0; ac < WME_NUM_AC; ac++) {
		/* set WME values for CCK modulation */
		wmep = &iwi_wme_cck_params[ac];
		sc->wme[1].aifsn[ac] = wmep->wmep_aifsn;
		sc->wme[1].cwmin[ac] = IWI_EXP2(wmep->wmep_logcwmin);
		sc->wme[1].cwmax[ac] = IWI_EXP2(wmep->wmep_logcwmax);
		sc->wme[1].burst[ac] = IWI_USEC(wmep->wmep_txopLimit);
		sc->wme[1].acm[ac]   = wmep->wmep_acm;

		/* set WME values for OFDM modulation */
		wmep = &iwi_wme_ofdm_params[ac];
		sc->wme[2].aifsn[ac] = wmep->wmep_aifsn;
		sc->wme[2].cwmin[ac] = IWI_EXP2(wmep->wmep_logcwmin);
		sc->wme[2].cwmax[ac] = IWI_EXP2(wmep->wmep_logcwmax);
		sc->wme[2].burst[ac] = IWI_USEC(wmep->wmep_txopLimit);
		sc->wme[2].acm[ac]   = wmep->wmep_acm;
	}
}