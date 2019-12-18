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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  scalar_t__ pcell_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  clock ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  OF_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 
 int quicc_bfe_probe (int /*<<< orphan*/ ,uintptr_t) ; 

__attribute__((used)) static int
quicc_fdt_probe(device_t dev)
{
	phandle_t par;
	pcell_t clock;

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (!ofw_bus_is_compatible(dev, "fsl,cpm2"))
		return (ENXIO);

	par = OF_parent(ofw_bus_get_node(dev));
	if (OF_getprop(par, "bus-frequency", &clock, sizeof(clock)) <= 0)
		clock = 0;

	return (quicc_bfe_probe(dev, (uintptr_t)clock));
}