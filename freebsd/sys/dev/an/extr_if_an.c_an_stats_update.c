#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int if_drv_flags; } ;
struct TYPE_4__ {int an_len; int /*<<< orphan*/  an_type; } ;
struct TYPE_3__ {int an_len; int an_opmode; int /*<<< orphan*/  an_type; } ;
struct an_softc {scalar_t__ an_timer; int an_associated; int /*<<< orphan*/  an_stat_ch; TYPE_2__ an_stats; TYPE_1__ an_status; struct ifnet* an_ifp; } ;
struct an_ltv_status {int dummy; } ;
struct an_ltv_stats {int dummy; } ;
struct an_ltv_gen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AN_LOCK_ASSERT (struct an_softc*) ; 
 int /*<<< orphan*/  AN_RID_32BITS_CUM ; 
 int /*<<< orphan*/  AN_RID_STATUS ; 
 int AN_STATUS_OPMODE_IN_SYNC ; 
 int IFF_DRV_OACTIVE ; 
 scalar_t__ an_read_record (struct an_softc*,struct an_ltv_gen*) ; 
 int /*<<< orphan*/  an_watchdog (struct an_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct an_softc*) ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void
an_stats_update(void *xsc)
{
	struct an_softc		*sc;
	struct ifnet		*ifp;

	sc = xsc;
	AN_LOCK_ASSERT(sc);
	ifp = sc->an_ifp;
	if (sc->an_timer > 0 && --sc->an_timer == 0)
		an_watchdog(sc);

	sc->an_status.an_type = AN_RID_STATUS;
	sc->an_status.an_len = sizeof(struct an_ltv_status);
	if (an_read_record(sc, (struct an_ltv_gen *)&sc->an_status))
		return;

	if (sc->an_status.an_opmode & AN_STATUS_OPMODE_IN_SYNC)
		sc->an_associated = 1;
	else
		sc->an_associated = 0;

	/* Don't do this while we're transmitting */
	if (ifp->if_drv_flags & IFF_DRV_OACTIVE) {
		callout_reset(&sc->an_stat_ch, hz, an_stats_update, sc);
		return;
	}

	sc->an_stats.an_len = sizeof(struct an_ltv_stats);
	sc->an_stats.an_type = AN_RID_32BITS_CUM;
	if (an_read_record(sc, (struct an_ltv_gen *)&sc->an_stats.an_len))
		return;

	callout_reset(&sc->an_stat_ch, hz, an_stats_update, sc);

	return;
}