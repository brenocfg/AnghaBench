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
struct lp_data {int /*<<< orphan*/ * sc_ifbuf; TYPE_1__* sc_ifp; int /*<<< orphan*/  sc_dev; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; struct lp_data* if_softc; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ if_mtu; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IRQENABLE ; 
 scalar_t__ MLPIPHDRLEN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PPB_COMPATIBLE ; 
 int /*<<< orphan*/  PPB_DONTWAIT ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ lpinittables () ; 
 int /*<<< orphan*/ * malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_assert_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ppb_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wctr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpinit_locked(struct ifnet *ifp)
{
	struct lp_data *sc = ifp->if_softc;
	device_t dev = sc->sc_dev;
	device_t ppbus = device_get_parent(dev);
	int error;

	ppb_assert_locked(ppbus);
	error = ppb_request_bus(ppbus, dev, PPB_DONTWAIT);
	if (error)
		return (error);

	/* Now IFF_UP means that we own the bus */
	ppb_set_mode(ppbus, PPB_COMPATIBLE);

	if (lpinittables()) {
		ppb_release_bus(ppbus, dev);
		return (ENOBUFS);
	}

	sc->sc_ifbuf = malloc(sc->sc_ifp->if_mtu + MLPIPHDRLEN,
	    M_DEVBUF, M_NOWAIT);
	if (sc->sc_ifbuf == NULL) {
		ppb_release_bus(ppbus, dev);
		return (ENOBUFS);
	}

	ppb_wctr(ppbus, IRQENABLE);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
	return (0);
}