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
struct request {int dummy; } ;
struct mtip_cmd {int /*<<< orphan*/  command_dma; int /*<<< orphan*/  command; } ;
struct driver_data {TYPE_1__* pdev; } ;
struct blk_mq_tag_set {struct driver_data* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DMA_ALLOC_SZ ; 
 struct mtip_cmd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtip_free_cmd(struct blk_mq_tag_set *set, struct request *rq,
			  unsigned int hctx_idx)
{
	struct driver_data *dd = set->driver_data;
	struct mtip_cmd *cmd = blk_mq_rq_to_pdu(rq);

	if (!cmd->command)
		return;

	dma_free_coherent(&dd->pdev->dev, CMD_DMA_ALLOC_SZ, cmd->command,
			  cmd->command_dma);
}