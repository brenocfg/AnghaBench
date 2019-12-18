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
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct bcma_device {TYPE_1__ dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct device_node* bcma_of_find_child_device (struct device*,struct bcma_device*) ; 
 int /*<<< orphan*/  bcma_of_get_irq (struct device*,struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_dma_configure (TYPE_1__*,struct device_node*,int) ; 

__attribute__((used)) static void bcma_of_fill_device(struct device *parent,
				struct bcma_device *core)
{
	struct device_node *node;

	node = bcma_of_find_child_device(parent, core);
	if (node)
		core->dev.of_node = node;

	core->irq = bcma_of_get_irq(parent, core, 0);

	of_dma_configure(&core->dev, node, false);
}