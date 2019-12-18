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
struct uart_phyp_softc {int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int uart_phyp_probe_node (struct uart_phyp_softc*) ; 

__attribute__((used)) static int
uart_phyp_probe(device_t dev)
{
	const char *name;
	struct uart_phyp_softc sc;
	int err;

	name = ofw_bus_get_name(dev);
	if (name == NULL || strcmp(name, "vty") != 0)
		return (ENXIO);

	sc.node = ofw_bus_get_node(dev);
	err = uart_phyp_probe_node(&sc);
	if (err != 0)
		return (err);

	device_set_desc(dev, "POWER Hypervisor Virtual Serial Port");

	return (err);
}