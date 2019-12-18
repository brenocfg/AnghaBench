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
struct uart_softc {scalar_t__ sc_irid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct uart_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int uart_bus_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_pci_detach(device_t dev)
{
	struct uart_softc *sc;

	sc = device_get_softc(dev);

	if (sc->sc_irid != 0)
		pci_release_msi(dev);

	return (uart_bus_detach(dev));
}