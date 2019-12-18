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
struct arm_gic_softc {int /*<<< orphan*/  gic_res; int /*<<< orphan*/ * gic_irqs; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  arm_gic_spec ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct arm_gic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
arm_gic_detach(device_t dev)
{
	struct arm_gic_softc *sc;

	sc = device_get_softc(dev);

	if (sc->gic_irqs != NULL)
		free(sc->gic_irqs, M_DEVBUF);

	bus_release_resources(dev, arm_gic_spec, sc->gic_res);

	return (0);
}