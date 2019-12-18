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
struct atse_softc {int /*<<< orphan*/ * atse_mem_res; int /*<<< orphan*/  atse_mem_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct atse_softc* device_get_softc (int /*<<< orphan*/ ) ; 

void
atse_detach_resources(device_t dev)
{
	struct atse_softc *sc;

	sc = device_get_softc(dev);

	if (sc->atse_mem_res != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY, sc->atse_mem_rid,
		    sc->atse_mem_res);
		sc->atse_mem_res = NULL;
	}
}