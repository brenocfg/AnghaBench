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
struct lp_data {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * sc_ifbuf; TYPE_1__* sc_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_assert_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wctr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lpstop(struct lp_data *sc)
{
	device_t ppbus = device_get_parent(sc->sc_dev);

	ppb_assert_locked(ppbus);
	ppb_wctr(ppbus, 0x00);
	sc->sc_ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	free(sc->sc_ifbuf, M_DEVBUF);
	sc->sc_ifbuf = NULL;

	/* IFF_UP is not set, try to release the bus anyway */
	ppb_release_bus(ppbus, sc->sc_dev);
}