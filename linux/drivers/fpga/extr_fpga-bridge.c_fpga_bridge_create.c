#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fpga_bridge_ops {int /*<<< orphan*/  groups; } ;
struct TYPE_3__ {int id; int /*<<< orphan*/  of_node; struct device* parent; int /*<<< orphan*/  class; int /*<<< orphan*/  groups; } ;
struct fpga_bridge {char const* name; TYPE_1__ dev; void* priv; struct fpga_bridge_ops const* br_ops; int /*<<< orphan*/  node; int /*<<< orphan*/  mutex; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dev_set_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  fpga_bridge_class ; 
 int /*<<< orphan*/  fpga_bridge_ida ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct fpga_bridge*) ; 
 struct fpga_bridge* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

struct fpga_bridge *fpga_bridge_create(struct device *dev, const char *name,
				       const struct fpga_bridge_ops *br_ops,
				       void *priv)
{
	struct fpga_bridge *bridge;
	int id, ret = 0;

	if (!name || !strlen(name)) {
		dev_err(dev, "Attempt to register with no name!\n");
		return NULL;
	}

	bridge = kzalloc(sizeof(*bridge), GFP_KERNEL);
	if (!bridge)
		return NULL;

	id = ida_simple_get(&fpga_bridge_ida, 0, 0, GFP_KERNEL);
	if (id < 0) {
		ret = id;
		goto error_kfree;
	}

	mutex_init(&bridge->mutex);
	INIT_LIST_HEAD(&bridge->node);

	bridge->name = name;
	bridge->br_ops = br_ops;
	bridge->priv = priv;

	device_initialize(&bridge->dev);
	bridge->dev.groups = br_ops->groups;
	bridge->dev.class = fpga_bridge_class;
	bridge->dev.parent = dev;
	bridge->dev.of_node = dev->of_node;
	bridge->dev.id = id;

	ret = dev_set_name(&bridge->dev, "br%d", id);
	if (ret)
		goto error_device;

	return bridge;

error_device:
	ida_simple_remove(&fpga_bridge_ida, id);
error_kfree:
	kfree(bridge);

	return NULL;
}