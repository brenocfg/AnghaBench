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
struct uhso_softc {TYPE_1__* sc_ifp; int /*<<< orphan*/ * sc_if_xfer; } ;
struct TYPE_2__ {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 size_t UHSO_IFNET_READ ; 
 size_t UHSO_IFNET_WRITE ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uhso_if_stop(struct uhso_softc *sc)
{

	usbd_transfer_stop(sc->sc_if_xfer[UHSO_IFNET_READ]);
	usbd_transfer_stop(sc->sc_if_xfer[UHSO_IFNET_WRITE]);
	sc->sc_ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
}