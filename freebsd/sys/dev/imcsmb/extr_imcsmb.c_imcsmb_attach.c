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
struct imcsmb_softc {int /*<<< orphan*/ * smbus; int /*<<< orphan*/  regs; int /*<<< orphan*/  imcsmb_pci; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct imcsmb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
imcsmb_attach(device_t dev)
{
	struct imcsmb_softc *sc;
	int rc;

	/* Initialize private state */
	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->imcsmb_pci = device_get_parent(dev);
	sc->regs = device_get_ivars(dev);

	/* Create the smbus child */
	sc->smbus = device_add_child(dev, "smbus", -1);
	if (sc->smbus == NULL) {
		/* Nothing has been allocated, so there's no cleanup. */
		device_printf(dev, "Child smbus not added\n");
		rc = ENXIO;
		goto out;
	}

	/* Attach the smbus child. */
	if ((rc = bus_generic_attach(dev)) != 0) {
		device_printf(dev, "Failed to attach smbus: %d\n", rc);
	}

out:
	return (rc);
}