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
struct device {struct device_node* of_node; } ;
struct fpga_region {int /*<<< orphan*/  bridge_list; struct fpga_image_info* info; struct device dev; } ;
struct fpga_image_info {struct device_node* overlay; } ;
struct device_node {struct device_node* parent; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  fpga_bridges_put (int /*<<< orphan*/ *) ; 
 int of_fpga_bridge_get_to_list (struct device_node*,struct fpga_image_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int) ; 

__attribute__((used)) static int of_fpga_region_get_bridges(struct fpga_region *region)
{
	struct device *dev = &region->dev;
	struct device_node *region_np = dev->of_node;
	struct fpga_image_info *info = region->info;
	struct device_node *br, *np, *parent_br = NULL;
	int i, ret;

	/* If parent is a bridge, add to list */
	ret = of_fpga_bridge_get_to_list(region_np->parent, info,
					 &region->bridge_list);

	/* -EBUSY means parent is a bridge that is under use. Give up. */
	if (ret == -EBUSY)
		return ret;

	/* Zero return code means parent was a bridge and was added to list. */
	if (!ret)
		parent_br = region_np->parent;

	/* If overlay has a list of bridges, use it. */
	br = of_parse_phandle(info->overlay, "fpga-bridges", 0);
	if (br) {
		of_node_put(br);
		np = info->overlay;
	} else {
		np = region_np;
	}

	for (i = 0; ; i++) {
		br = of_parse_phandle(np, "fpga-bridges", i);
		if (!br)
			break;

		/* If parent bridge is in list, skip it. */
		if (br == parent_br) {
			of_node_put(br);
			continue;
		}

		/* If node is a bridge, get it and add to list */
		ret = of_fpga_bridge_get_to_list(br, info,
						 &region->bridge_list);
		of_node_put(br);

		/* If any of the bridges are in use, give up */
		if (ret == -EBUSY) {
			fpga_bridges_put(&region->bridge_list);
			return -EBUSY;
		}
	}

	return 0;
}