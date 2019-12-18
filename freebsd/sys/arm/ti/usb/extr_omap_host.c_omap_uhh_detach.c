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
struct omap_uhh_softc {int /*<<< orphan*/ * uhh_mem_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct omap_uhh_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_uhh_fini (struct omap_uhh_softc*) ; 

__attribute__((used)) static int
omap_uhh_detach(device_t dev)
{
	struct omap_uhh_softc *isc = device_get_softc(dev);

	/* during module unload there are lots of children leftover */
	device_delete_children(dev);

	if (isc->uhh_mem_res) {
		bus_release_resource(dev, SYS_RES_MEMORY, 0, isc->uhh_mem_res);
		isc->uhh_mem_res = NULL;
	}

	omap_uhh_fini(isc);

	return (0);
}