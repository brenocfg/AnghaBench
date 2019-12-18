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
typedef  int u64 ;
struct request {int tag; } ;
struct mtip_port {int flags; int* cmds_to_issue; struct mtip_cmd_hdr* command_list; } ;
struct mtip_cmd_hdr {scalar_t__ byte_count; void* opts; void* ctbau; void* ctba; } ;
struct mtip_cmd {unsigned int scatter_ents; int unaligned; int command_dma; int direction; struct host_to_dev_fis* command; int /*<<< orphan*/  retries; int /*<<< orphan*/  sg; } ;
struct host_to_dev_fis {int type; int opts; int lba_low; int lba_mid; int lba_hi; int lba_low_ex; int lba_mid_ex; int lba_hi_ex; int device; unsigned int features; unsigned int features_ex; int sect_count; scalar_t__ res3; scalar_t__ res2; scalar_t__ control; scalar_t__ sect_cnt_ex; int /*<<< orphan*/  command; } ;
struct driver_data {struct mtip_port* port; TYPE_1__* pdev; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int AHCI_CMD_PREFETCH ; 
 int /*<<< orphan*/  ATA_CMD_FPDMA_READ ; 
 int /*<<< orphan*/  ATA_CMD_FPDMA_WRITE ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int /*<<< orphan*/  MTIP_MAX_RETRIES ; 
 int /*<<< orphan*/  MTIP_PF_HOST_CAP_64 ; 
 int MTIP_PF_ISSUE_CMDS_BIT ; 
 int MTIP_PF_PAUSE_IO ; 
 scalar_t__ READ ; 
 unsigned int blk_rq_map_sg (int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 int blk_rq_pos (struct request*) ; 
 unsigned int blk_rq_sectors (struct request*) ; 
 void* cpu_to_le32 (unsigned int) ; 
 unsigned int dma_map_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  fill_command_sg (struct driver_data*,struct mtip_cmd*,unsigned int) ; 
 int /*<<< orphan*/  mtip_issue_ncq_command (struct mtip_port*,int) ; 
 int /*<<< orphan*/  prefetch (int*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  set_bit (int,int*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mtip_hw_submit_io(struct driver_data *dd, struct request *rq,
			      struct mtip_cmd *command,
			      struct blk_mq_hw_ctx *hctx)
{
	struct mtip_cmd_hdr *hdr =
		dd->port->command_list + sizeof(struct mtip_cmd_hdr) * rq->tag;
	struct host_to_dev_fis	*fis;
	struct mtip_port *port = dd->port;
	int dma_dir = rq_data_dir(rq) == READ ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
	u64 start = blk_rq_pos(rq);
	unsigned int nsect = blk_rq_sectors(rq);
	unsigned int nents;

	/* Map the scatter list for DMA access */
	nents = blk_rq_map_sg(hctx->queue, rq, command->sg);
	nents = dma_map_sg(&dd->pdev->dev, command->sg, nents, dma_dir);

	prefetch(&port->flags);

	command->scatter_ents = nents;

	/*
	 * The number of retries for this command before it is
	 * reported as a failure to the upper layers.
	 */
	command->retries = MTIP_MAX_RETRIES;

	/* Fill out fis */
	fis = command->command;
	fis->type        = 0x27;
	fis->opts        = 1 << 7;
	if (dma_dir == DMA_FROM_DEVICE)
		fis->command = ATA_CMD_FPDMA_READ;
	else
		fis->command = ATA_CMD_FPDMA_WRITE;
	fis->lba_low     = start & 0xFF;
	fis->lba_mid     = (start >> 8) & 0xFF;
	fis->lba_hi      = (start >> 16) & 0xFF;
	fis->lba_low_ex  = (start >> 24) & 0xFF;
	fis->lba_mid_ex  = (start >> 32) & 0xFF;
	fis->lba_hi_ex   = (start >> 40) & 0xFF;
	fis->device	 = 1 << 6;
	fis->features    = nsect & 0xFF;
	fis->features_ex = (nsect >> 8) & 0xFF;
	fis->sect_count  = ((rq->tag << 3) | (rq->tag >> 5));
	fis->sect_cnt_ex = 0;
	fis->control     = 0;
	fis->res2        = 0;
	fis->res3        = 0;
	fill_command_sg(dd, command, nents);

	if (unlikely(command->unaligned))
		fis->device |= 1 << 7;

	/* Populate the command header */
	hdr->ctba = cpu_to_le32(command->command_dma & 0xFFFFFFFF);
	if (test_bit(MTIP_PF_HOST_CAP_64, &dd->port->flags))
		hdr->ctbau = cpu_to_le32((command->command_dma >> 16) >> 16);
	hdr->opts = cpu_to_le32((nents << 16) | 5 | AHCI_CMD_PREFETCH);
	hdr->byte_count = 0;

	command->direction = dma_dir;

	/*
	 * To prevent this command from being issued
	 * if an internal command is in progress or error handling is active.
	 */
	if (unlikely(port->flags & MTIP_PF_PAUSE_IO)) {
		set_bit(rq->tag, port->cmds_to_issue);
		set_bit(MTIP_PF_ISSUE_CMDS_BIT, &port->flags);
		return;
	}

	/* Issue the command to the hardware */
	mtip_issue_ncq_command(port, rq->tag);
}