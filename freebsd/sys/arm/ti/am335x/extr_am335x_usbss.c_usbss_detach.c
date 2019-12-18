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
struct usbss_softc {scalar_t__ sc_mem_res; int /*<<< orphan*/  sc_mem_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct usbss_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
usbss_detach(device_t dev)
{
	struct usbss_softc *sc = device_get_softc(dev);

	/* Free resources if any */
	if (sc->sc_mem_res)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_mem_rid,
		    sc->sc_mem_res);

	/* during module unload there are lots of children leftover */
	device_delete_children(dev);

	return (0);
}