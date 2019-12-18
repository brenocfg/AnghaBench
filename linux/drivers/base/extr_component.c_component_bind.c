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
struct master {int /*<<< orphan*/  dev; } ;
struct component {int bound; TYPE_1__* ops; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int (* bind ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_close_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devres_open_group (int /*<<< orphan*/ ,struct component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_release_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devres_remove_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int component_bind(struct component *component, struct master *master,
	void *data)
{
	int ret;

	/*
	 * Each component initialises inside its own devres group.
	 * This allows us to roll-back a failed component without
	 * affecting anything else.
	 */
	if (!devres_open_group(master->dev, NULL, GFP_KERNEL))
		return -ENOMEM;

	/*
	 * Also open a group for the device itself: this allows us
	 * to release the resources claimed against the sub-device
	 * at the appropriate moment.
	 */
	if (!devres_open_group(component->dev, component, GFP_KERNEL)) {
		devres_release_group(master->dev, NULL);
		return -ENOMEM;
	}

	dev_dbg(master->dev, "binding %s (ops %ps)\n",
		dev_name(component->dev), component->ops);

	ret = component->ops->bind(component->dev, master->dev, data);
	if (!ret) {
		component->bound = true;

		/*
		 * Close the component device's group so that resources
		 * allocated in the binding are encapsulated for removal
		 * at unbind.  Remove the group on the DRM device as we
		 * can clean those resources up independently.
		 */
		devres_close_group(component->dev, NULL);
		devres_remove_group(master->dev, NULL);

		dev_info(master->dev, "bound %s (ops %ps)\n",
			 dev_name(component->dev), component->ops);
	} else {
		devres_release_group(component->dev, NULL);
		devres_release_group(master->dev, NULL);

		dev_err(master->dev, "failed to bind %s (ops %ps): %d\n",
			dev_name(component->dev), component->ops, ret);
	}

	return ret;
}