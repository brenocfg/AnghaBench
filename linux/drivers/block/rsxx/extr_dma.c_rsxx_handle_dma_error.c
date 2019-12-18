#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  discards_failed; int /*<<< orphan*/  writes_failed; int /*<<< orphan*/  reads_failed; int /*<<< orphan*/  reads_retried; int /*<<< orphan*/  soft_errors; int /*<<< orphan*/  hard_errors; int /*<<< orphan*/  crc_errors; } ;
struct rsxx_dma_ctrl {TYPE_2__* card; TYPE_1__ stats; } ;
struct rsxx_dma {int cmd; int /*<<< orphan*/  laddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  scrub_hard; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (TYPE_2__*) ; 
 unsigned int DMA_HW_FAULT ; 
 unsigned int DMA_SW_ERR ; 
#define  HW_CMD_BLK_DISCARD 131 
#define  HW_CMD_BLK_READ 130 
#define  HW_CMD_BLK_RECON_READ 129 
#define  HW_CMD_BLK_WRITE 128 
 int HW_STATUS_CRC ; 
 int HW_STATUS_FAULT ; 
 int HW_STATUS_HARD_ERR ; 
 int HW_STATUS_SOFT_ERR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rsxx_complete_dma (struct rsxx_dma_ctrl*,struct rsxx_dma*,unsigned int) ; 
 int /*<<< orphan*/  rsxx_requeue_dma (struct rsxx_dma_ctrl*,struct rsxx_dma*) ; 

__attribute__((used)) static void rsxx_handle_dma_error(struct rsxx_dma_ctrl *ctrl,
				      struct rsxx_dma *dma,
				      u8 hw_st)
{
	unsigned int status = 0;
	int requeue_cmd = 0;

	dev_dbg(CARD_TO_DEV(ctrl->card),
		"Handling DMA error(cmd x%02x, laddr x%08x st:x%02x)\n",
		dma->cmd, dma->laddr, hw_st);

	if (hw_st & HW_STATUS_CRC)
		ctrl->stats.crc_errors++;
	if (hw_st & HW_STATUS_HARD_ERR)
		ctrl->stats.hard_errors++;
	if (hw_st & HW_STATUS_SOFT_ERR)
		ctrl->stats.soft_errors++;

	switch (dma->cmd) {
	case HW_CMD_BLK_READ:
		if (hw_st & (HW_STATUS_CRC | HW_STATUS_HARD_ERR)) {
			if (ctrl->card->scrub_hard) {
				dma->cmd = HW_CMD_BLK_RECON_READ;
				requeue_cmd = 1;
				ctrl->stats.reads_retried++;
			} else {
				status |= DMA_HW_FAULT;
				ctrl->stats.reads_failed++;
			}
		} else if (hw_st & HW_STATUS_FAULT) {
			status |= DMA_HW_FAULT;
			ctrl->stats.reads_failed++;
		}

		break;
	case HW_CMD_BLK_RECON_READ:
		if (hw_st & (HW_STATUS_CRC | HW_STATUS_HARD_ERR)) {
			/* Data could not be reconstructed. */
			status |= DMA_HW_FAULT;
			ctrl->stats.reads_failed++;
		}

		break;
	case HW_CMD_BLK_WRITE:
		status |= DMA_HW_FAULT;
		ctrl->stats.writes_failed++;

		break;
	case HW_CMD_BLK_DISCARD:
		status |= DMA_HW_FAULT;
		ctrl->stats.discards_failed++;

		break;
	default:
		dev_err(CARD_TO_DEV(ctrl->card),
			"Unknown command in DMA!(cmd: x%02x "
			   "laddr x%08x st: x%02x\n",
			   dma->cmd, dma->laddr, hw_st);
		status |= DMA_SW_ERR;

		break;
	}

	if (requeue_cmd)
		rsxx_requeue_dma(ctrl, dma);
	else
		rsxx_complete_dma(ctrl, dma, status);
}