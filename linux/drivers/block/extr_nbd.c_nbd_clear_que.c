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
struct nbd_device {TYPE_1__* disk; int /*<<< orphan*/  tag_set; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_quiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_tagset_busy_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disk_to_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  nbd_clear_req ; 

__attribute__((used)) static void nbd_clear_que(struct nbd_device *nbd)
{
	blk_mq_quiesce_queue(nbd->disk->queue);
	blk_mq_tagset_busy_iter(&nbd->tag_set, nbd_clear_req, NULL);
	blk_mq_unquiesce_queue(nbd->disk->queue);
	dev_dbg(disk_to_dev(nbd->disk), "queue cleared\n");
}