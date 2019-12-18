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
struct fw_device {struct fw_device* config_rom; TYPE_1__* node; struct fw_card* card; } ;
struct fw_card {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_card_put (struct fw_card*) ; 
 struct fw_device* fw_device (struct device*) ; 
 int /*<<< orphan*/  fw_node_put (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct fw_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fw_device_release(struct device *dev)
{
	struct fw_device *device = fw_device(dev);
	struct fw_card *card = device->card;
	unsigned long flags;

	/*
	 * Take the card lock so we don't set this to NULL while a
	 * FW_NODE_UPDATED callback is being handled or while the
	 * bus manager work looks at this node.
	 */
	spin_lock_irqsave(&card->lock, flags);
	device->node->data = NULL;
	spin_unlock_irqrestore(&card->lock, flags);

	fw_node_put(device->node);
	kfree(device->config_rom);
	kfree(device);
	fw_card_put(card);
}