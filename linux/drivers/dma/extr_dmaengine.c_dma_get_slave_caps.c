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
struct dma_slave_caps {int cmd_pause; int cmd_resume; int cmd_terminate; int /*<<< orphan*/  descriptor_reuse; int /*<<< orphan*/  residue_granularity; int /*<<< orphan*/  max_burst; scalar_t__ directions; int /*<<< orphan*/  dst_addr_widths; int /*<<< orphan*/  src_addr_widths; } ;
struct TYPE_2__ {int /*<<< orphan*/  bits; } ;
struct dma_device {int /*<<< orphan*/  device_terminate_all; int /*<<< orphan*/  device_resume; int /*<<< orphan*/  device_pause; int /*<<< orphan*/  descriptor_reuse; int /*<<< orphan*/  residue_granularity; int /*<<< orphan*/  max_burst; scalar_t__ directions; int /*<<< orphan*/  dst_addr_widths; int /*<<< orphan*/  src_addr_widths; TYPE_1__ cap_mask; } ;
struct dma_chan {struct dma_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CYCLIC ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dma_get_slave_caps(struct dma_chan *chan, struct dma_slave_caps *caps)
{
	struct dma_device *device;

	if (!chan || !caps)
		return -EINVAL;

	device = chan->device;

	/* check if the channel supports slave transactions */
	if (!(test_bit(DMA_SLAVE, device->cap_mask.bits) ||
	      test_bit(DMA_CYCLIC, device->cap_mask.bits)))
		return -ENXIO;

	/*
	 * Check whether it reports it uses the generic slave
	 * capabilities, if not, that means it doesn't support any
	 * kind of slave capabilities reporting.
	 */
	if (!device->directions)
		return -ENXIO;

	caps->src_addr_widths = device->src_addr_widths;
	caps->dst_addr_widths = device->dst_addr_widths;
	caps->directions = device->directions;
	caps->max_burst = device->max_burst;
	caps->residue_granularity = device->residue_granularity;
	caps->descriptor_reuse = device->descriptor_reuse;
	caps->cmd_pause = !!device->device_pause;
	caps->cmd_resume = !!device->device_resume;
	caps->cmd_terminate = !!device->device_terminate_all;

	return 0;
}