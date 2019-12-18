#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * regs_res; int /*<<< orphan*/  regs_rid; int /*<<< orphan*/ * intr_res; int /*<<< orphan*/  intr_rid; scalar_t__ platform_attached; } ;
typedef  TYPE_1__ ig4iic_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int ig4iic_detach (TYPE_1__*) ; 

__attribute__((used)) static int
ig4iic_acpi_detach(device_t dev)
{
	ig4iic_softc_t *sc = device_get_softc(dev);
	int error;

	if (sc->platform_attached) {
		error = ig4iic_detach(sc);
		if (error)
			return (error);
		sc->platform_attached = 0;
	}

	if (sc->intr_res) {
		bus_release_resource(dev, SYS_RES_IRQ,
				     sc->intr_rid, sc->intr_res);
		sc->intr_res = NULL;
	}
	if (sc->regs_res) {
		bus_release_resource(dev, SYS_RES_MEMORY,
				     sc->regs_rid, sc->regs_res);
		sc->regs_res = NULL;
	}

	return (0);
}