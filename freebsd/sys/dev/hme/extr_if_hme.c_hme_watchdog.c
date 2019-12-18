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
typedef  int /*<<< orphan*/  u_int ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;
struct hme_softc {scalar_t__ sc_wdog_timer; int sc_flags; int /*<<< orphan*/  sc_dev; struct ifnet* sc_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int EJUSTRETURN ; 
 int HME_LINK ; 
 int /*<<< orphan*/  HME_LOCK_ASSERT (struct hme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HME_SEBI_STAT ; 
 scalar_t__ HME_SEB_READ_4 (struct hme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  KTR_HME ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hme_init_locked (struct hme_softc*) ; 
 int /*<<< orphan*/  hme_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hme_watchdog(struct hme_softc *sc)
{
	struct ifnet *ifp = sc->sc_ifp;

	HME_LOCK_ASSERT(sc, MA_OWNED);

#ifdef HMEDEBUG
	CTR1(KTR_HME, "hme_watchdog: status %x",
	    (u_int)HME_SEB_READ_4(sc, HME_SEBI_STAT));
#endif

	if (sc->sc_wdog_timer == 0 || --sc->sc_wdog_timer != 0)
		return (0);

	if ((sc->sc_flags & HME_LINK) != 0)
		device_printf(sc->sc_dev, "device timeout\n");
	else if (bootverbose)
		device_printf(sc->sc_dev, "device timeout (no link)\n");
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);

	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	hme_init_locked(sc);
	hme_start_locked(ifp);
	return (EJUSTRETURN);
}