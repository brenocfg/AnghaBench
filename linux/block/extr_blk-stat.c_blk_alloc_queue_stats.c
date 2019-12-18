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
struct blk_queue_stats {int enable_accounting; int /*<<< orphan*/  lock; int /*<<< orphan*/  callbacks; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct blk_queue_stats* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct blk_queue_stats *blk_alloc_queue_stats(void)
{
	struct blk_queue_stats *stats;

	stats = kmalloc(sizeof(*stats), GFP_KERNEL);
	if (!stats)
		return NULL;

	INIT_LIST_HEAD(&stats->callbacks);
	spin_lock_init(&stats->lock);
	stats->enable_accounting = false;

	return stats;
}