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
struct lp_data {int /*<<< orphan*/  res_irq; int /*<<< orphan*/  sc_intr_cookie; int /*<<< orphan*/  sc_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bpfdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct lp_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpstop (struct lp_data*) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lp_detach(device_t dev)
{
	struct lp_data *sc = device_get_softc(dev);
	device_t ppbus = device_get_parent(dev);

	ppb_lock(ppbus);
	lpstop(sc);
	ppb_unlock(ppbus);
	bpfdetach(sc->sc_ifp);
	if_detach(sc->sc_ifp);
	bus_teardown_intr(dev, sc->res_irq, sc->sc_intr_cookie);
	bus_release_resource(dev, SYS_RES_IRQ, 0, sc->res_irq);
	return (0);
}