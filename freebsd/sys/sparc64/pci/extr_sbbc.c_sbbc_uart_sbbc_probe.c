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
struct uart_softc {int /*<<< orphan*/ * sc_class; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SBBC_PCI_BAR ; 
 struct uart_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int uart_bus_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_sbbc_class ; 

__attribute__((used)) static int
sbbc_uart_sbbc_probe(device_t dev)
{
	struct uart_softc *sc;

	sc = device_get_softc(dev);
	sc->sc_class = &uart_sbbc_class;
	device_set_desc(dev, "Serengeti console");
	return (uart_bus_probe(dev, 0, 0, 0, SBBC_PCI_BAR, 0, 0));
}