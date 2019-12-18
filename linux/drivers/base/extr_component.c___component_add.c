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
struct device {int dummy; } ;
struct component_ops {int dummy; } ;
struct component {int subcomponent; int /*<<< orphan*/  node; scalar_t__ master; struct device* dev; struct component_ops const* ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  component_list ; 
 int /*<<< orphan*/  component_mutex ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct component_ops const*) ; 
 int /*<<< orphan*/  kfree (struct component*) ; 
 struct component* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_component (scalar_t__,struct component*) ; 
 int try_to_bring_up_masters (struct component*) ; 

__attribute__((used)) static int __component_add(struct device *dev, const struct component_ops *ops,
	int subcomponent)
{
	struct component *component;
	int ret;

	component = kzalloc(sizeof(*component), GFP_KERNEL);
	if (!component)
		return -ENOMEM;

	component->ops = ops;
	component->dev = dev;
	component->subcomponent = subcomponent;

	dev_dbg(dev, "adding component (ops %ps)\n", ops);

	mutex_lock(&component_mutex);
	list_add_tail(&component->node, &component_list);

	ret = try_to_bring_up_masters(component);
	if (ret < 0) {
		if (component->master)
			remove_component(component->master, component);
		list_del(&component->node);

		kfree(component);
	}
	mutex_unlock(&component_mutex);

	return ret < 0 ? ret : 0;
}