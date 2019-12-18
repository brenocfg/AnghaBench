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
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR_CTRL ; 
 int /*<<< orphan*/  HI3620_CTRL ; 
 int /*<<< orphan*/  ctrl_base ; 
 int /*<<< orphan*/  id ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int hi3xxx_hotplug_init(void)
{
	struct device_node *node;

	node = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (!node) {
		id = ERROR_CTRL;
		return -ENOENT;
	}

	ctrl_base = of_iomap(node, 0);
	of_node_put(node);
	if (!ctrl_base) {
		id = ERROR_CTRL;
		return -ENOMEM;
	}

	id = HI3620_CTRL;
	return 0;
}