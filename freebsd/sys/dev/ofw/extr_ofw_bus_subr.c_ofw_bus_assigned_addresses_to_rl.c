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
struct resource_list {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ofw_bus_reg_to_rl_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource_list*,char*) ; 

int
ofw_bus_assigned_addresses_to_rl(device_t dev, phandle_t node, pcell_t acells,
    pcell_t scells, struct resource_list *rl)
{

	return (ofw_bus_reg_to_rl_helper(dev, node, acells, scells,
	    rl, "assigned-addresses"));
}