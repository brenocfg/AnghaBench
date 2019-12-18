#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request {TYPE_2__* q; } ;
struct mtip_cmd {int /*<<< orphan*/  status; int /*<<< orphan*/  unaligned; int /*<<< orphan*/  direction; int /*<<< orphan*/  scatter_ents; int /*<<< orphan*/  sg; } ;
struct driver_data {TYPE_1__* port; TYPE_3__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct driver_data* queuedata; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmd_slot_unal; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 struct mtip_cmd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtip_softirq_done_fn(struct request *rq)
{
	struct mtip_cmd *cmd = blk_mq_rq_to_pdu(rq);
	struct driver_data *dd = rq->q->queuedata;

	/* Unmap the DMA scatter list entries */
	dma_unmap_sg(&dd->pdev->dev, cmd->sg, cmd->scatter_ents,
							cmd->direction);

	if (unlikely(cmd->unaligned))
		atomic_inc(&dd->port->cmd_slot_unal);

	blk_mq_end_request(rq, cmd->status);
}