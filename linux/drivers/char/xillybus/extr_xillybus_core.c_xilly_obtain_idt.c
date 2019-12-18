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
struct xilly_endpoint {scalar_t__ idtlen; int /*<<< orphan*/  dev; TYPE_1__* ephw; scalar_t__ fatal_error; scalar_t__ registers; struct xilly_channel** channels; } ;
struct xilly_channel {int wr_sleepy; TYPE_2__** wr_buffers; int /*<<< orphan*/  wr_buf_size; int /*<<< orphan*/  endpoint; int /*<<< orphan*/  wr_wait; } ;
struct TYPE_4__ {scalar_t__ end_offset; unsigned char* addr; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* hw_sync_sgl_for_cpu ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  XILLY_TIMEOUT ; 
 scalar_t__ crc32_le (int /*<<< orphan*/ ,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fpga_buf_ctrl_reg ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xilly_obtain_idt(struct xilly_endpoint *endpoint)
{
	struct xilly_channel *channel;
	unsigned char *version;
	long t;

	channel = endpoint->channels[1]; /* This should be generated ad-hoc */

	channel->wr_sleepy = 1;

	iowrite32(1 |
		  (3 << 24), /* Opcode 3 for channel 0 = Send IDT */
		  endpoint->registers + fpga_buf_ctrl_reg);

	t = wait_event_interruptible_timeout(channel->wr_wait,
					     (!channel->wr_sleepy),
					     XILLY_TIMEOUT);

	if (t <= 0) {
		dev_err(endpoint->dev, "Failed to obtain IDT. Aborting.\n");

		if (endpoint->fatal_error)
			return -EIO;

		return -ENODEV;
	}

	endpoint->ephw->hw_sync_sgl_for_cpu(
		channel->endpoint,
		channel->wr_buffers[0]->dma_addr,
		channel->wr_buf_size,
		DMA_FROM_DEVICE);

	if (channel->wr_buffers[0]->end_offset != endpoint->idtlen) {
		dev_err(endpoint->dev,
			"IDT length mismatch (%d != %d). Aborting.\n",
			channel->wr_buffers[0]->end_offset, endpoint->idtlen);
		return -ENODEV;
	}

	if (crc32_le(~0, channel->wr_buffers[0]->addr,
		     endpoint->idtlen+1) != 0) {
		dev_err(endpoint->dev, "IDT failed CRC check. Aborting.\n");
		return -ENODEV;
	}

	version = channel->wr_buffers[0]->addr;

	/* Check version number. Reject anything above 0x82. */
	if (*version > 0x82) {
		dev_err(endpoint->dev,
			"No support for IDT version 0x%02x. Maybe the xillybus driver needs an upgrade. Aborting.\n",
			*version);
		return -ENODEV;
	}

	return 0;
}