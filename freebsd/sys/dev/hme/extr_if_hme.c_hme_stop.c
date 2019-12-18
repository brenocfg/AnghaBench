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
typedef  int u_int32_t ;
struct hme_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_flags; TYPE_1__* sc_ifp; scalar_t__ sc_wdog_timer; int /*<<< orphan*/  sc_tick_ch; } ;
struct TYPE_2__ {int if_drv_flags; } ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  HME_LINK ; 
 int /*<<< orphan*/  HME_SEBI_IMASK ; 
 int /*<<< orphan*/  HME_SEBI_RESET ; 
 int /*<<< orphan*/  HME_SEB_BARRIER (struct hme_softc*,int /*<<< orphan*/ ,int,int) ; 
 int HME_SEB_READ_4 (struct hme_softc*,int /*<<< orphan*/ ) ; 
 int HME_SEB_RESET_ERX ; 
 int HME_SEB_RESET_ETX ; 
 int /*<<< orphan*/  HME_SEB_WRITE_4 (struct hme_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
hme_stop(struct hme_softc *sc)
{
	u_int32_t v;
	int n;

	callout_stop(&sc->sc_tick_ch);
	sc->sc_wdog_timer = 0;
	sc->sc_ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	sc->sc_flags &= ~HME_LINK;

	/* Mask all interrupts */
	HME_SEB_WRITE_4(sc, HME_SEBI_IMASK, 0xffffffff);

	/* Reset transmitter and receiver */
	HME_SEB_WRITE_4(sc, HME_SEBI_RESET, HME_SEB_RESET_ETX |
	    HME_SEB_RESET_ERX);
	HME_SEB_BARRIER(sc, HME_SEBI_RESET, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	for (n = 0; n < 20; n++) {
		v = HME_SEB_READ_4(sc, HME_SEBI_RESET);
		if ((v & (HME_SEB_RESET_ETX | HME_SEB_RESET_ERX)) == 0)
			return;
		DELAY(20);
	}

	device_printf(sc->sc_dev, "hme_stop: reset failed\n");
}