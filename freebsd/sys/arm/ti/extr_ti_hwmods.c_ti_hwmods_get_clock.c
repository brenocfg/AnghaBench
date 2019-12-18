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
struct hwmod {int clock_id; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int clk_ident_t ;

/* Variables and functions */
 int INVALID_CLK_IDENT ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int strlen (char*) ; 
 int ti_get_hwmods_prop (int /*<<< orphan*/ ,void**) ; 
 struct hwmod* ti_hwmods ; 

clk_ident_t
ti_hwmods_get_clock(device_t dev)
{
	phandle_t node;
	int len, l;
	char *name;
	char *buf;
	int clk;
	struct hwmod *hw;

	if ((node = ofw_bus_get_node(dev)) == 0)
		return (INVALID_CLK_IDENT);

	if ((len = ti_get_hwmods_prop(node, (void **)&name)) <= 0)
		return (INVALID_CLK_IDENT);

	buf = name;

	clk = INVALID_CLK_IDENT;
	while ((len > 0) && (clk == INVALID_CLK_IDENT)) {
		for (hw = ti_hwmods; hw->name != NULL; ++hw) {
			if (strcmp(hw->name, name) == 0) {
				clk = hw->clock_id;
				break;
			}
		}

		/* Slide to the next sub-string. */
		l = strlen(name) + 1;
		name += l;
		len -= l;
	}

	if (len > 0)
		device_printf(dev, "WARNING: more than one ti,hwmod \n");

	OF_prop_free(buf);
	return (clk);
}