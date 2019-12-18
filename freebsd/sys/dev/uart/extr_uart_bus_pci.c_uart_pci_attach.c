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
struct uart_softc {int sc_irid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct uart_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_msi_count (int /*<<< orphan*/ ) ; 
 int uart_bus_attach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_pci_attach(device_t dev)
{
	struct uart_softc *sc;
	int count;

	sc = device_get_softc(dev);

	/*
	 * Use MSI in preference to legacy IRQ if available.
	 * Whilst some PCIe UARTs support >1 MSI vector, use only the first.
	 */
	if (pci_msi_count(dev) > 0) {
		count = 1;
		if (pci_alloc_msi(dev, &count) == 0) {
			sc->sc_irid = 1;
			device_printf(dev, "Using %d MSI message\n", count);
		}
	}

	return (uart_bus_attach(dev));
}