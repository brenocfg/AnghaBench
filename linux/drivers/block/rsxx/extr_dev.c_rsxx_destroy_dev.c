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
struct rsxx_cardinfo {int /*<<< orphan*/  major; TYPE_1__* queue; int /*<<< orphan*/ * gendisk; } ;
struct TYPE_2__ {int /*<<< orphan*/ * queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  blk_cleanup_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  enable_blkdev ; 
 int /*<<< orphan*/  put_disk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_blkdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rsxx_destroy_dev(struct rsxx_cardinfo *card)
{
	if (!enable_blkdev)
		return;

	put_disk(card->gendisk);
	card->gendisk = NULL;

	blk_cleanup_queue(card->queue);
	card->queue->queuedata = NULL;
	unregister_blkdev(card->major, DRIVER_NAME);
}