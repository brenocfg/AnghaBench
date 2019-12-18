#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct subsys_dev_iter {scalar_t__ type; int /*<<< orphan*/  ki; } ;
struct klist_node {int dummy; } ;
struct device {scalar_t__ type; } ;
struct TYPE_2__ {struct device* device; } ;

/* Variables and functions */
 struct klist_node* klist_next (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_device_private_bus (struct klist_node*) ; 

struct device *subsys_dev_iter_next(struct subsys_dev_iter *iter)
{
	struct klist_node *knode;
	struct device *dev;

	for (;;) {
		knode = klist_next(&iter->ki);
		if (!knode)
			return NULL;
		dev = to_device_private_bus(knode)->device;
		if (!iter->type || iter->type == dev->type)
			return dev;
	}
}