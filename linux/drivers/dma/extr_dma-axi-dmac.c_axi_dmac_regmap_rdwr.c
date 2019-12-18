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
struct device {int dummy; } ;

/* Variables and functions */
#define  AXI_DMAC_REG_ACTIVE_TRANSFER_ID 147 
#define  AXI_DMAC_REG_CTRL 146 
#define  AXI_DMAC_REG_CURRENT_DEST_ADDR 145 
#define  AXI_DMAC_REG_CURRENT_SRC_ADDR 144 
#define  AXI_DMAC_REG_DEST_ADDRESS 143 
#define  AXI_DMAC_REG_DEST_STRIDE 142 
#define  AXI_DMAC_REG_FLAGS 141 
#define  AXI_DMAC_REG_IRQ_MASK 140 
#define  AXI_DMAC_REG_IRQ_PENDING 139 
#define  AXI_DMAC_REG_IRQ_SOURCE 138 
#define  AXI_DMAC_REG_PARTIAL_XFER_ID 137 
#define  AXI_DMAC_REG_PARTIAL_XFER_LEN 136 
#define  AXI_DMAC_REG_SRC_ADDRESS 135 
#define  AXI_DMAC_REG_SRC_STRIDE 134 
#define  AXI_DMAC_REG_START_TRANSFER 133 
#define  AXI_DMAC_REG_STATUS 132 
#define  AXI_DMAC_REG_TRANSFER_DONE 131 
#define  AXI_DMAC_REG_TRANSFER_ID 130 
#define  AXI_DMAC_REG_X_LENGTH 129 
#define  AXI_DMAC_REG_Y_LENGTH 128 

__attribute__((used)) static bool axi_dmac_regmap_rdwr(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case AXI_DMAC_REG_IRQ_MASK:
	case AXI_DMAC_REG_IRQ_SOURCE:
	case AXI_DMAC_REG_IRQ_PENDING:
	case AXI_DMAC_REG_CTRL:
	case AXI_DMAC_REG_TRANSFER_ID:
	case AXI_DMAC_REG_START_TRANSFER:
	case AXI_DMAC_REG_FLAGS:
	case AXI_DMAC_REG_DEST_ADDRESS:
	case AXI_DMAC_REG_SRC_ADDRESS:
	case AXI_DMAC_REG_X_LENGTH:
	case AXI_DMAC_REG_Y_LENGTH:
	case AXI_DMAC_REG_DEST_STRIDE:
	case AXI_DMAC_REG_SRC_STRIDE:
	case AXI_DMAC_REG_TRANSFER_DONE:
	case AXI_DMAC_REG_ACTIVE_TRANSFER_ID:
	case AXI_DMAC_REG_STATUS:
	case AXI_DMAC_REG_CURRENT_SRC_ADDR:
	case AXI_DMAC_REG_CURRENT_DEST_ADDR:
	case AXI_DMAC_REG_PARTIAL_XFER_LEN:
	case AXI_DMAC_REG_PARTIAL_XFER_ID:
		return true;
	default:
		return false;
	}
}