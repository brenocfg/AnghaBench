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
typedef  int u_int ;
struct hme_softc {TYPE_1__* sc_ifp; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HME_MIFI_CFG ; 
 int /*<<< orphan*/  HME_MIFI_SM ; 
 int /*<<< orphan*/  HME_MIFI_STAT ; 
 int /*<<< orphan*/  HME_MIF_READ_4 (struct hme_softc*,int /*<<< orphan*/ ) ; 
 int HME_SEB_STAT_FATAL_ERRORS ; 
 int HME_SEB_STAT_MIFIRQ ; 
 int /*<<< orphan*/  HME_WHINE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hme_init_locked (struct hme_softc*) ; 

__attribute__((used)) static void
hme_eint(struct hme_softc *sc, u_int status)
{

	if ((status & HME_SEB_STAT_MIFIRQ) != 0) {
		device_printf(sc->sc_dev, "XXXlink status changed: "
		    "cfg=%#x, stat=%#x, sm=%#x\n",
		    HME_MIF_READ_4(sc, HME_MIFI_CFG),
		    HME_MIF_READ_4(sc, HME_MIFI_STAT),
		    HME_MIF_READ_4(sc, HME_MIFI_SM));
		return;
	}

	/* check for fatal errors that needs reset to unfreeze DMA engine */
	if ((status & HME_SEB_STAT_FATAL_ERRORS) != 0) {
		HME_WHINE(sc->sc_dev, "error signaled, status=%#x\n", status);
		sc->sc_ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		hme_init_locked(sc);
	}
}