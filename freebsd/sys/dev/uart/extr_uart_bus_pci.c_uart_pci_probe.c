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
struct pci_id {scalar_t__ desc; int /*<<< orphan*/  rid; int /*<<< orphan*/  rclk; int /*<<< orphan*/  regshft; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 struct uart_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_ns8250_ids ; 
 int uart_bus_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_ns8250_class ; 
 struct pci_id* uart_pci_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_pci_probe(device_t dev)
{
	struct uart_softc *sc;
	const struct pci_id *id;
	int result;

	sc = device_get_softc(dev);

	id = uart_pci_match(dev, pci_ns8250_ids);
	if (id != NULL) {
		sc->sc_class = &uart_ns8250_class;
		goto match;
	}
	/* Add checks for non-ns8250 IDs here. */
	return (ENXIO);

 match:
	result = uart_bus_probe(dev, id->regshft, 0, id->rclk, id->rid, 0, 0);
	/* Bail out on error. */
	if (result > 0)
		return (result);
	/* Set/override the device description. */
	if (id->desc)
		device_set_desc(dev, id->desc);
	return (result);
}