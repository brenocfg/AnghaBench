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
struct ace_device {int /*<<< orphan*/  baseaddr; scalar_t__ irq; int /*<<< orphan*/  fsm_tasklet; int /*<<< orphan*/  tag_set; scalar_t__ queue; scalar_t__ gd; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (scalar_t__) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct ace_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (scalar_t__) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ace_teardown(struct ace_device *ace)
{
	if (ace->gd) {
		del_gendisk(ace->gd);
		put_disk(ace->gd);
	}

	if (ace->queue) {
		blk_cleanup_queue(ace->queue);
		blk_mq_free_tag_set(&ace->tag_set);
	}

	tasklet_kill(&ace->fsm_tasklet);

	if (ace->irq)
		free_irq(ace->irq, ace);

	iounmap(ace->baseaddr);
}