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
struct axi_dmac_chan {int hw_cyclic; int hw_2d; int max_length; scalar_t__ dest_type; scalar_t__ src_type; int hw_partial_xfer; int length_align_mask; int address_align_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct axi_dmac {TYPE_1__ dma_dev; struct axi_dmac_chan chan; } ;

/* Variables and functions */
 unsigned int ADI_AXI_PCORE_VER (int,int,char) ; 
 int /*<<< orphan*/  ADI_AXI_REG_VERSION ; 
 scalar_t__ AXI_DMAC_BUS_TYPE_AXI_MM ; 
 int AXI_DMAC_FLAG_CYCLIC ; 
 int /*<<< orphan*/  AXI_DMAC_REG_DEST_ADDRESS ; 
 int /*<<< orphan*/  AXI_DMAC_REG_FLAGS ; 
 int /*<<< orphan*/  AXI_DMAC_REG_SRC_ADDRESS ; 
 int /*<<< orphan*/  AXI_DMAC_REG_X_LENGTH ; 
 int /*<<< orphan*/  AXI_DMAC_REG_Y_LENGTH ; 
 int ENODEV ; 
 int UINT_MAX ; 
 int axi_dmac_read (struct axi_dmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axi_dmac_write (struct axi_dmac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int axi_dmac_detect_caps(struct axi_dmac *dmac)
{
	struct axi_dmac_chan *chan = &dmac->chan;
	unsigned int version;

	version = axi_dmac_read(dmac, ADI_AXI_REG_VERSION);

	axi_dmac_write(dmac, AXI_DMAC_REG_FLAGS, AXI_DMAC_FLAG_CYCLIC);
	if (axi_dmac_read(dmac, AXI_DMAC_REG_FLAGS) == AXI_DMAC_FLAG_CYCLIC)
		chan->hw_cyclic = true;

	axi_dmac_write(dmac, AXI_DMAC_REG_Y_LENGTH, 1);
	if (axi_dmac_read(dmac, AXI_DMAC_REG_Y_LENGTH) == 1)
		chan->hw_2d = true;

	axi_dmac_write(dmac, AXI_DMAC_REG_X_LENGTH, 0xffffffff);
	chan->max_length = axi_dmac_read(dmac, AXI_DMAC_REG_X_LENGTH);
	if (chan->max_length != UINT_MAX)
		chan->max_length++;

	axi_dmac_write(dmac, AXI_DMAC_REG_DEST_ADDRESS, 0xffffffff);
	if (axi_dmac_read(dmac, AXI_DMAC_REG_DEST_ADDRESS) == 0 &&
	    chan->dest_type == AXI_DMAC_BUS_TYPE_AXI_MM) {
		dev_err(dmac->dma_dev.dev,
			"Destination memory-mapped interface not supported.");
		return -ENODEV;
	}

	axi_dmac_write(dmac, AXI_DMAC_REG_SRC_ADDRESS, 0xffffffff);
	if (axi_dmac_read(dmac, AXI_DMAC_REG_SRC_ADDRESS) == 0 &&
	    chan->src_type == AXI_DMAC_BUS_TYPE_AXI_MM) {
		dev_err(dmac->dma_dev.dev,
			"Source memory-mapped interface not supported.");
		return -ENODEV;
	}

	if (version >= ADI_AXI_PCORE_VER(4, 2, 'a'))
		chan->hw_partial_xfer = true;

	if (version >= ADI_AXI_PCORE_VER(4, 1, 'a')) {
		axi_dmac_write(dmac, AXI_DMAC_REG_X_LENGTH, 0x00);
		chan->length_align_mask =
			axi_dmac_read(dmac, AXI_DMAC_REG_X_LENGTH);
	} else {
		chan->length_align_mask = chan->address_align_mask;
	}

	return 0;
}