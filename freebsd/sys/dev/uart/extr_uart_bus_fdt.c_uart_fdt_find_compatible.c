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
struct ofw_compat_data {int /*<<< orphan*/ * ocd_str; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 scalar_t__ ofw_bus_node_is_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const struct ofw_compat_data *
uart_fdt_find_compatible(phandle_t node, const struct ofw_compat_data *cd)
{
	const struct ofw_compat_data *ocd;

	for (ocd = cd; ocd->ocd_str != NULL; ocd++) {
		if (ofw_bus_node_is_compatible(node, ocd->ocd_str))
			return (ocd);
	}
	return (NULL);
}