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
struct nullb_device {int size; int /*<<< orphan*/  zone_nr_conv; int /*<<< orphan*/  zone_size; int /*<<< orphan*/  zoned; int /*<<< orphan*/  use_per_node_hctx; int /*<<< orphan*/  blocking; int /*<<< orphan*/  hw_queue_depth; int /*<<< orphan*/  irqmode; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  queue_mode; int /*<<< orphan*/  home_node; int /*<<< orphan*/  submit_queues; int /*<<< orphan*/  completion_nsec; int /*<<< orphan*/  badblocks; int /*<<< orphan*/  cache; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ badblocks_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_blocking ; 
 int /*<<< orphan*/  g_bs ; 
 int /*<<< orphan*/  g_completion_nsec ; 
 int g_gb ; 
 int /*<<< orphan*/  g_home_node ; 
 int /*<<< orphan*/  g_hw_queue_depth ; 
 int /*<<< orphan*/  g_irqmode ; 
 int /*<<< orphan*/  g_queue_mode ; 
 int /*<<< orphan*/  g_submit_queues ; 
 int /*<<< orphan*/  g_use_per_node_hctx ; 
 int /*<<< orphan*/  g_zone_nr_conv ; 
 int /*<<< orphan*/  g_zone_size ; 
 int /*<<< orphan*/  g_zoned ; 
 int /*<<< orphan*/  kfree (struct nullb_device*) ; 
 struct nullb_device* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nullb_device *null_alloc_dev(void)
{
	struct nullb_device *dev;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return NULL;
	INIT_RADIX_TREE(&dev->data, GFP_ATOMIC);
	INIT_RADIX_TREE(&dev->cache, GFP_ATOMIC);
	if (badblocks_init(&dev->badblocks, 0)) {
		kfree(dev);
		return NULL;
	}

	dev->size = g_gb * 1024;
	dev->completion_nsec = g_completion_nsec;
	dev->submit_queues = g_submit_queues;
	dev->home_node = g_home_node;
	dev->queue_mode = g_queue_mode;
	dev->blocksize = g_bs;
	dev->irqmode = g_irqmode;
	dev->hw_queue_depth = g_hw_queue_depth;
	dev->blocking = g_blocking;
	dev->use_per_node_hctx = g_use_per_node_hctx;
	dev->zoned = g_zoned;
	dev->zone_size = g_zone_size;
	dev->zone_nr_conv = g_zone_nr_conv;
	return dev;
}