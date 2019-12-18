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
typedef  int u_int ;
struct tegra_pcib_softc {int /*<<< orphan*/  irq_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct tegra_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int intr_map_clone_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tegra_pcib_route_interrupt(device_t bus, device_t dev, int pin)
{
	struct tegra_pcib_softc *sc;
	u_int irq;

	sc = device_get_softc(bus);
	irq = intr_map_clone_irq(rman_get_start(sc->irq_res));
	device_printf(bus, "route pin %d for device %d.%d to %u\n",
		      pin, pci_get_slot(dev), pci_get_function(dev),
		      irq);

	return (irq);
}