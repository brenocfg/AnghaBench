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
struct imcsmb_pci_softc {scalar_t__ semaphore; int /*<<< orphan*/ * dev; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char*,int) ; 
 struct imcsmb_pci_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * imcsmb_regs ; 

__attribute__((used)) static int
imcsmb_pci_attach(device_t dev)
{
	struct imcsmb_pci_softc *sc;
	device_t child;
	int rc;
	int unit;

	/* Initialize private state */
	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->semaphore = 0;

	/* Create the imcsmbX children */
	for (unit = 0; unit < 2; unit++) {
		child = device_add_child(dev, "imcsmb", -1);
		if (child == NULL) {
			/* Nothing has been allocated, so there's no cleanup. */
			device_printf(dev, "Child imcsmb not added\n");
			rc = ENXIO;
			goto out;
		}
		/* Set the child's ivars to point to the appropriate set of
		 * the PCI device's registers.
		 */
		device_set_ivars(child, &imcsmb_regs[unit]);
	}

	/* Attach the imcsmbX children. */
	if ((rc = bus_generic_attach(dev)) != 0) {
		device_printf(dev, "failed to attach children: %d\n", rc);
		goto out;
	}

out:
	return (rc);
}