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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int n_sg; struct fit_sg_descriptor* sksg_list; int /*<<< orphan*/  sksg_dma_address; int /*<<< orphan*/  id; } ;
struct skd_special_context {TYPE_2__ req; int /*<<< orphan*/  db_dma_address; int /*<<< orphan*/  mb_dma_address; scalar_t__ msg_buf; } ;
struct skd_device {int dbg_level; TYPE_1__* pdev; } ;
struct fit_sg_descriptor {int byte_count; int /*<<< orphan*/  next_desc_ptr; int /*<<< orphan*/  host_side_addr; int /*<<< orphan*/  control; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  FIT_QCMD_MSGSIZE_128 ; 
 int /*<<< orphan*/  FIT_QCMD_QID_NORMAL ; 
 int /*<<< orphan*/  FIT_Q_COMMAND ; 
 int SKD_N_SPECIAL_FITMSG_BYTES ; 
 int /*<<< orphan*/  SKD_WRITEQ (struct skd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void skd_send_special_fitmsg(struct skd_device *skdev,
				    struct skd_special_context *skspcl)
{
	u64 qcmd;

	WARN_ON_ONCE(skspcl->req.n_sg != 1);

	if (unlikely(skdev->dbg_level > 1)) {
		u8 *bp = (u8 *)skspcl->msg_buf;
		int i;

		for (i = 0; i < SKD_N_SPECIAL_FITMSG_BYTES; i += 8) {
			dev_dbg(&skdev->pdev->dev, " spcl[%2d] %8ph\n", i,
				&bp[i]);
			if (i == 0)
				i = 64 - 8;
		}

		dev_dbg(&skdev->pdev->dev,
			"skspcl=%p id=%04x sksg_list=%p sksg_dma=%pad\n",
			skspcl, skspcl->req.id, skspcl->req.sksg_list,
			&skspcl->req.sksg_dma_address);
		for (i = 0; i < skspcl->req.n_sg; i++) {
			struct fit_sg_descriptor *sgd =
				&skspcl->req.sksg_list[i];

			dev_dbg(&skdev->pdev->dev,
				"  sg[%d] count=%u ctrl=0x%x addr=0x%llx next=0x%llx\n",
				i, sgd->byte_count, sgd->control,
				sgd->host_side_addr, sgd->next_desc_ptr);
		}
	}

	/*
	 * Special FIT msgs are always 128 bytes: a 64-byte FIT hdr
	 * and one 64-byte SSDI command.
	 */
	qcmd = skspcl->mb_dma_address;
	qcmd |= FIT_QCMD_QID_NORMAL + FIT_QCMD_MSGSIZE_128;

	dma_sync_single_for_device(&skdev->pdev->dev, skspcl->mb_dma_address,
				   SKD_N_SPECIAL_FITMSG_BYTES, DMA_TO_DEVICE);
	dma_sync_single_for_device(&skdev->pdev->dev,
				   skspcl->req.sksg_dma_address,
				   1 * sizeof(struct fit_sg_descriptor),
				   DMA_TO_DEVICE);
	dma_sync_single_for_device(&skdev->pdev->dev,
				   skspcl->db_dma_address,
				   skspcl->req.sksg_list[0].byte_count,
				   DMA_BIDIRECTIONAL);

	/* Make sure skd_msg_buf is written before the doorbell is triggered. */
	smp_wmb();

	SKD_WRITEQ(skdev, qcmd, FIT_Q_COMMAND);
}