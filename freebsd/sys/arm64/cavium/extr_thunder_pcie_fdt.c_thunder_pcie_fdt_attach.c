#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int coherent; int /*<<< orphan*/  ecam; } ;
struct generic_pcie_fdt_softc {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct generic_pcie_fdt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_host_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thunder_pcie_identify_ecam (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
thunder_pcie_fdt_attach(device_t dev)
{
	struct generic_pcie_fdt_softc *sc;

	sc = device_get_softc(dev);
	thunder_pcie_identify_ecam(dev, &sc->base.ecam);
	sc->base.coherent = 1;

	return (pci_host_generic_attach(dev));
}