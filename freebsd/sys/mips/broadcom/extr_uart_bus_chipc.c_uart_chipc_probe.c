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
typedef  int /*<<< orphan*/  u_int ;
struct uart_softc {int /*<<< orphan*/ * sc_class; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_get_platform () ; 
 int /*<<< orphan*/  bcm_get_uart_rclk (int /*<<< orphan*/ ) ; 
 struct uart_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int uart_bus_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_ns8250_class ; 

__attribute__((used)) static int
uart_chipc_probe(device_t dev)
{
	struct uart_softc 	*sc;
	u_int			 rclk;

	sc = device_get_softc(dev);
	sc->sc_class = &uart_ns8250_class;

	rclk = bcm_get_uart_rclk(bcm_get_platform());
	return (uart_bus_probe(dev, 0, 0, rclk, 0, 0, 0));
}