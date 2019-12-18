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
typedef  int /*<<< orphan*/  fwohci_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwohci_stop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fwohci_pci_suspend(device_t dev)
{
	fwohci_softc_t *sc = device_get_softc(dev);
	int err;

	device_printf(dev, "fwohci_pci_suspend\n");
	err = bus_generic_suspend(dev);
	if (err)
		return err;
	fwohci_stop(sc, dev);
	return 0;
}