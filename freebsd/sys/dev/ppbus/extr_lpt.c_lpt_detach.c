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
struct lpt_data {int /*<<< orphan*/  sc_statbuf; int /*<<< orphan*/  sc_inbuf; int /*<<< orphan*/ * sc_intr_resource; int /*<<< orphan*/  sc_intr_cookie; int /*<<< orphan*/  sc_timer; int /*<<< orphan*/  sc_cdev_bypass; int /*<<< orphan*/  sc_cdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct lpt_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpt_release_ppbus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpt_detach(device_t dev)
{
	struct lpt_data *sc = DEVTOSOFTC(dev);
	device_t ppbus = device_get_parent(dev);

	destroy_dev(sc->sc_cdev);
	destroy_dev(sc->sc_cdev_bypass);
	ppb_lock(ppbus);
	lpt_release_ppbus(dev);
	ppb_unlock(ppbus);
	callout_drain(&sc->sc_timer);
	if (sc->sc_intr_resource != NULL) {
		bus_teardown_intr(dev, sc->sc_intr_resource,
		    sc->sc_intr_cookie);
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_intr_resource);
	}
	free(sc->sc_inbuf, M_DEVBUF);
	free(sc->sc_statbuf, M_DEVBUF);

	return (0);
}