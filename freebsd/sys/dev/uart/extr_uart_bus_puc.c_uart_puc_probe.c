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
 scalar_t__ BUS_READ_IVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  PUC_IVAR_CLOCK ; 
 int /*<<< orphan*/  PUC_IVAR_TYPE ; 
 uintptr_t PUC_TYPE_SERIAL ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct uart_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int uart_bus_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_ns8250_class ; 

__attribute__((used)) static int
uart_puc_probe(device_t dev)
{
	device_t parent;
	struct uart_softc *sc;
	uintptr_t rclk, type;

	parent = device_get_parent(dev);
	sc = device_get_softc(dev);

	if (BUS_READ_IVAR(parent, dev, PUC_IVAR_TYPE, &type))
		return (ENXIO);
	if (type != PUC_TYPE_SERIAL)
		return (ENXIO);

	sc->sc_class = &uart_ns8250_class;

	if (BUS_READ_IVAR(parent, dev, PUC_IVAR_CLOCK, &rclk))
		rclk = 0;
	return (uart_bus_probe(dev, 0, 0, rclk, 0, 0, 0));
}