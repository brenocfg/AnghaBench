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
struct fw_node {int /*<<< orphan*/  node_id; struct fw_device* data; } ;
struct fw_device {int /*<<< orphan*/  workfn; scalar_t__ config_rom_retries; int /*<<< orphan*/  generation; int /*<<< orphan*/  node_id; int /*<<< orphan*/  max_speed; struct fw_node* node; int /*<<< orphan*/  state; int /*<<< orphan*/  config_rom; struct fw_card* card; } ;
struct fw_card {int /*<<< orphan*/  lock; struct fw_node* root_node; int /*<<< orphan*/  generation; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ FW_DEVICE_GONE ; 
 int /*<<< orphan*/  FW_DEVICE_RUNNING ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct fw_device* fw_device (struct device*) ; 
 int /*<<< orphan*/  fw_device_rwsem ; 
 int /*<<< orphan*/  fw_device_update ; 
 int /*<<< orphan*/  fw_notice (struct fw_card*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_schedule_bm_work (struct fw_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_schedule_device_work (struct fw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_fw_device (struct device*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lookup_existing_device(struct device *dev, void *data)
{
	struct fw_device *old = fw_device(dev);
	struct fw_device *new = data;
	struct fw_card *card = new->card;
	int match = 0;

	if (!is_fw_device(dev))
		return 0;

	down_read(&fw_device_rwsem); /* serialize config_rom access */
	spin_lock_irq(&card->lock);  /* serialize node access */

	if (memcmp(old->config_rom, new->config_rom, 6 * 4) == 0 &&
	    atomic_cmpxchg(&old->state,
			   FW_DEVICE_GONE,
			   FW_DEVICE_RUNNING) == FW_DEVICE_GONE) {
		struct fw_node *current_node = new->node;
		struct fw_node *obsolete_node = old->node;

		new->node = obsolete_node;
		new->node->data = new;
		old->node = current_node;
		old->node->data = old;

		old->max_speed = new->max_speed;
		old->node_id = current_node->node_id;
		smp_wmb();  /* update node_id before generation */
		old->generation = card->generation;
		old->config_rom_retries = 0;
		fw_notice(card, "rediscovered device %s\n", dev_name(dev));

		old->workfn = fw_device_update;
		fw_schedule_device_work(old, 0);

		if (current_node == card->root_node)
			fw_schedule_bm_work(card, 0);

		match = 1;
	}

	spin_unlock_irq(&card->lock);
	up_read(&fw_device_rwsem);

	return match;
}