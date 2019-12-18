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
struct itwd_softc {scalar_t__ intr_res; int /*<<< orphan*/  intr_rid; scalar_t__ intr_handle; int /*<<< orphan*/ * wd_ev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct itwd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_list ; 
 int /*<<< orphan*/  wd_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
itwd_detach(device_t dev)
{
	struct itwd_softc *sc = device_get_softc(dev);
	int dummy;

	if (sc->wd_ev != NULL)
		EVENTHANDLER_DEREGISTER(watchdog_list, sc->wd_ev);
	wd_func(dev, 0, &dummy);
	if (sc->intr_handle)
		bus_teardown_intr(dev, sc->intr_res, sc->intr_handle);
	if (sc->intr_res)
		bus_release_resource(dev, SYS_RES_IRQ, sc->intr_rid,
		    sc->intr_res);
	return (0);
}