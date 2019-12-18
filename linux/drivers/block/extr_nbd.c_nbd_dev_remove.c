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
struct request_queue {int dummy; } ;
struct nbd_device {scalar_t__ destroy_complete; int /*<<< orphan*/  flags; int /*<<< orphan*/  tag_set; struct gendisk* disk; } ;
struct gendisk {int /*<<< orphan*/ * private_data; struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBD_DESTROY_ON_DISCONNECT ; 
 int /*<<< orphan*/  blk_cleanup_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  del_gendisk (struct gendisk*) ; 
 int /*<<< orphan*/  kfree (struct nbd_device*) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nbd_dev_remove(struct nbd_device *nbd)
{
	struct gendisk *disk = nbd->disk;
	struct request_queue *q;

	if (disk) {
		q = disk->queue;
		del_gendisk(disk);
		blk_cleanup_queue(q);
		blk_mq_free_tag_set(&nbd->tag_set);
		disk->private_data = NULL;
		put_disk(disk);
	}

	/*
	 * Place this in the last just before the nbd is freed to
	 * make sure that the disk and the related kobject are also
	 * totally removed to avoid duplicate creation of the same
	 * one.
	 */
	if (test_bit(NBD_DESTROY_ON_DISCONNECT, &nbd->flags) && nbd->destroy_complete)
		complete(nbd->destroy_complete);

	kfree(nbd);
}