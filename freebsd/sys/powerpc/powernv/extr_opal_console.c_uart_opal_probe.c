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
struct uart_opal_softc {int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int uart_opal_probe_node (struct uart_opal_softc*) ; 

__attribute__((used)) static int
uart_opal_probe(device_t dev)
{
	struct uart_opal_softc sc;
	int err;

	sc.node = ofw_bus_get_node(dev);
	err = uart_opal_probe_node(&sc);
	if (err != 0)
		return (err);

	device_set_desc(dev, "OPAL Serial Port");

	return (err);
}