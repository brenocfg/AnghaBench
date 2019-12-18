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
struct fpga_manager_ops {int /*<<< orphan*/  groups; scalar_t__ write_sg; scalar_t__ write; int /*<<< orphan*/  write_init; int /*<<< orphan*/  state; int /*<<< orphan*/  write_complete; } ;
struct TYPE_3__ {int id; int /*<<< orphan*/  of_node; struct device* parent; int /*<<< orphan*/  groups; int /*<<< orphan*/  class; } ;
struct fpga_manager {char const* name; TYPE_1__ dev; void* priv; struct fpga_manager_ops const* mops; int /*<<< orphan*/  ref_mutex; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dev_set_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  fpga_mgr_class ; 
 int /*<<< orphan*/  fpga_mgr_ida ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct fpga_manager*) ; 
 struct fpga_manager* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

struct fpga_manager *fpga_mgr_create(struct device *dev, const char *name,
				     const struct fpga_manager_ops *mops,
				     void *priv)
{
	struct fpga_manager *mgr;
	int id, ret;

	if (!mops || !mops->write_complete || !mops->state ||
	    !mops->write_init || (!mops->write && !mops->write_sg) ||
	    (mops->write && mops->write_sg)) {
		dev_err(dev, "Attempt to register without fpga_manager_ops\n");
		return NULL;
	}

	if (!name || !strlen(name)) {
		dev_err(dev, "Attempt to register with no name!\n");
		return NULL;
	}

	mgr = kzalloc(sizeof(*mgr), GFP_KERNEL);
	if (!mgr)
		return NULL;

	id = ida_simple_get(&fpga_mgr_ida, 0, 0, GFP_KERNEL);
	if (id < 0) {
		ret = id;
		goto error_kfree;
	}

	mutex_init(&mgr->ref_mutex);

	mgr->name = name;
	mgr->mops = mops;
	mgr->priv = priv;

	device_initialize(&mgr->dev);
	mgr->dev.class = fpga_mgr_class;
	mgr->dev.groups = mops->groups;
	mgr->dev.parent = dev;
	mgr->dev.of_node = dev->of_node;
	mgr->dev.id = id;

	ret = dev_set_name(&mgr->dev, "fpga%d", id);
	if (ret)
		goto error_device;

	return mgr;

error_device:
	ida_simple_remove(&fpga_mgr_ida, id);
error_kfree:
	kfree(mgr);

	return NULL;
}