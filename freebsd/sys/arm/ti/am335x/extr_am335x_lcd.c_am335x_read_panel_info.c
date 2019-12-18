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
struct panel_info {int /*<<< orphan*/  sync_ctrl; int /*<<< orphan*/  sync_edge; int /*<<< orphan*/  fdd; int /*<<< orphan*/  bpp; int /*<<< orphan*/  dma_burst_sz; int /*<<< orphan*/  ac_bias_intrpt; int /*<<< orphan*/  ac_bias; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  am335x_read_property (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_bus_find_child (scalar_t__,char*) ; 

__attribute__((used)) static int
am335x_read_panel_info(device_t dev, phandle_t node, struct panel_info *panel)
{
	phandle_t panel_info_node;

	panel_info_node = ofw_bus_find_child(node, "panel-info");
	if (panel_info_node == 0)
		return (-1);

	am335x_read_property(dev, panel_info_node,
	    "ac-bias", &panel->ac_bias);

	am335x_read_property(dev, panel_info_node,
	    "ac-bias-intrpt", &panel->ac_bias_intrpt);

	am335x_read_property(dev, panel_info_node,
	    "dma-burst-sz", &panel->dma_burst_sz);

	am335x_read_property(dev, panel_info_node,
	    "bpp", &panel->bpp);

	am335x_read_property(dev, panel_info_node,
	    "fdd", &panel->fdd);

	am335x_read_property(dev, panel_info_node,
	    "sync-edge", &panel->sync_edge);

	am335x_read_property(dev, panel_info_node,
	    "sync-ctrl", &panel->sync_ctrl);

	return (0);
}