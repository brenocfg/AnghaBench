#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; struct device_node* of_node; struct device* parent; } ;
struct scmi_device {int id; int protocol_id; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int device_register (TYPE_1__*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct scmi_device*) ; 
 struct scmi_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  scmi_bus_id ; 
 int /*<<< orphan*/  scmi_bus_type ; 
 int /*<<< orphan*/  scmi_device_release ; 

struct scmi_device *
scmi_device_create(struct device_node *np, struct device *parent, int protocol)
{
	int id, retval;
	struct scmi_device *scmi_dev;

	scmi_dev = kzalloc(sizeof(*scmi_dev), GFP_KERNEL);
	if (!scmi_dev)
		return NULL;

	id = ida_simple_get(&scmi_bus_id, 1, 0, GFP_KERNEL);
	if (id < 0)
		goto free_mem;

	scmi_dev->id = id;
	scmi_dev->protocol_id = protocol;
	scmi_dev->dev.parent = parent;
	scmi_dev->dev.of_node = np;
	scmi_dev->dev.bus = &scmi_bus_type;
	scmi_dev->dev.release = scmi_device_release;
	dev_set_name(&scmi_dev->dev, "scmi_dev.%d", id);

	retval = device_register(&scmi_dev->dev);
	if (retval)
		goto put_dev;

	return scmi_dev;
put_dev:
	put_device(&scmi_dev->dev);
	ida_simple_remove(&scmi_bus_id, id);
free_mem:
	kfree(scmi_dev);
	return NULL;
}