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
struct mtip_cmd {int /*<<< orphan*/  sg; int /*<<< orphan*/  command; int /*<<< orphan*/  command_dma; } ;
struct driver_data {TYPE_1__* pdev; } ;
struct blk_mq_tag_set {struct driver_data* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DMA_ALLOC_SZ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTIP_MAX_SG ; 
 struct mtip_cmd* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtip_init_cmd(struct blk_mq_tag_set *set, struct request *rq,
			 unsigned int hctx_idx, unsigned int numa_node)
{
	struct driver_data *dd = set->driver_data;
	struct mtip_cmd *cmd = blk_mq_rq_to_pdu(rq);

	cmd->command = dma_alloc_coherent(&dd->pdev->dev, CMD_DMA_ALLOC_SZ,
			&cmd->command_dma, GFP_KERNEL);
	if (!cmd->command)
		return -ENOMEM;

	sg_init_table(cmd->sg, MTIP_MAX_SG);
	return 0;
}