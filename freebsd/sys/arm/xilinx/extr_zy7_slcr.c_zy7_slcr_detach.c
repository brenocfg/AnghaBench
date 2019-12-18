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
struct zy7_slcr_softc {int /*<<< orphan*/ * mem_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  ZSLCR_LOCK_DESTROY (struct zy7_slcr_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct zy7_slcr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zy7_slcr_softc_p ; 
 int /*<<< orphan*/ * zynq7_cpu_reset ; 

__attribute__((used)) static int
zy7_slcr_detach(device_t dev)
{
	struct zy7_slcr_softc *sc = device_get_softc(dev);

	bus_generic_detach(dev);

	/* Release memory resource. */
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY,
			     rman_get_rid(sc->mem_res), sc->mem_res);

	zy7_slcr_softc_p = NULL;
	zynq7_cpu_reset = NULL;

	ZSLCR_LOCK_DESTROY(sc);

	return (0);
}