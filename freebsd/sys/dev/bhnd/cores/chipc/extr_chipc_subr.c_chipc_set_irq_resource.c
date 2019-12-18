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
typedef  int /*<<< orphan*/  u_int ;
struct chipc_softc {scalar_t__ dev; } ;
struct chipc_devinfo {int irq_mapped; int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int bhnd_map_intr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_unmap_intr (scalar_t__,int /*<<< orphan*/ ) ; 
 int bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct chipc_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (scalar_t__,char*,...) ; 

int
chipc_set_irq_resource(struct chipc_softc *sc, device_t child, int rid,
    u_int intr)
{
	struct chipc_devinfo	*dinfo;
	int			 error;

	KASSERT(device_get_parent(child) == sc->dev, ("not a direct child"));
	dinfo = device_get_ivars(child);

	/* We currently only support a single IRQ mapping */
	if (dinfo->irq_mapped) {
		device_printf(sc->dev, "irq already mapped for child\n");
		return (ENOMEM);
	}

	/* Map the IRQ */
	if ((error = bhnd_map_intr(sc->dev, intr, &dinfo->irq))) {
		device_printf(sc->dev, "failed to map intr %u: %d\n", intr,
		    error);
		return (error);
	}

	dinfo->irq_mapped = true;

	/* Add to child's resource list */
	error = bus_set_resource(child, SYS_RES_IRQ, rid, dinfo->irq, 1);
	if (error) {
		device_printf(sc->dev, "failed to set child irq resource %d to "
		    "%ju: %d\n", rid, dinfo->irq, error);

		bhnd_unmap_intr(sc->dev, dinfo->irq);
		return (error);
	}

	return (0);
}