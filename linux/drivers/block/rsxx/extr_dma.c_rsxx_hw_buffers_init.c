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
struct TYPE_4__ {scalar_t__ idx; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/ * buf; } ;
struct TYPE_3__ {scalar_t__ idx; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/ * buf; } ;
struct rsxx_dma_ctrl {scalar_t__ regmap; TYPE_2__ cmd; TYPE_1__ status; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CB_ADD_HI ; 
 scalar_t__ CB_ADD_LO ; 
 int /*<<< orphan*/  COMMAND_BUFFER_SIZE8 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HW_CMD_IDX ; 
 scalar_t__ HW_STATUS_CNT ; 
 scalar_t__ RSXX_MAX_OUTSTANDING_CMDS ; 
 scalar_t__ SB_ADD_HI ; 
 scalar_t__ SB_ADD_LO ; 
 int /*<<< orphan*/  STATUS_BUFFER_SIZE8 ; 
 scalar_t__ SW_CMD_IDX ; 
 scalar_t__ SW_STATUS_CNT ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 scalar_t__ lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ upper_32_bits (int /*<<< orphan*/ ) ; 

int rsxx_hw_buffers_init(struct pci_dev *dev, struct rsxx_dma_ctrl *ctrl)
{
	ctrl->status.buf = dma_alloc_coherent(&dev->dev, STATUS_BUFFER_SIZE8,
				&ctrl->status.dma_addr, GFP_KERNEL);
	ctrl->cmd.buf = dma_alloc_coherent(&dev->dev, COMMAND_BUFFER_SIZE8,
				&ctrl->cmd.dma_addr, GFP_KERNEL);
	if (ctrl->status.buf == NULL || ctrl->cmd.buf == NULL)
		return -ENOMEM;

	memset(ctrl->status.buf, 0xac, STATUS_BUFFER_SIZE8);
	iowrite32(lower_32_bits(ctrl->status.dma_addr),
		ctrl->regmap + SB_ADD_LO);
	iowrite32(upper_32_bits(ctrl->status.dma_addr),
		ctrl->regmap + SB_ADD_HI);

	memset(ctrl->cmd.buf, 0x83, COMMAND_BUFFER_SIZE8);
	iowrite32(lower_32_bits(ctrl->cmd.dma_addr), ctrl->regmap + CB_ADD_LO);
	iowrite32(upper_32_bits(ctrl->cmd.dma_addr), ctrl->regmap + CB_ADD_HI);

	ctrl->status.idx = ioread32(ctrl->regmap + HW_STATUS_CNT);
	if (ctrl->status.idx > RSXX_MAX_OUTSTANDING_CMDS) {
		dev_crit(&dev->dev, "Failed reading status cnt x%x\n",
			ctrl->status.idx);
		return -EINVAL;
	}
	iowrite32(ctrl->status.idx, ctrl->regmap + HW_STATUS_CNT);
	iowrite32(ctrl->status.idx, ctrl->regmap + SW_STATUS_CNT);

	ctrl->cmd.idx = ioread32(ctrl->regmap + HW_CMD_IDX);
	if (ctrl->cmd.idx > RSXX_MAX_OUTSTANDING_CMDS) {
		dev_crit(&dev->dev, "Failed reading cmd cnt x%x\n",
			ctrl->status.idx);
		return -EINVAL;
	}
	iowrite32(ctrl->cmd.idx, ctrl->regmap + HW_CMD_IDX);
	iowrite32(ctrl->cmd.idx, ctrl->regmap + SW_CMD_IDX);

	return 0;
}