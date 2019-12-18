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
typedef  int u32 ;
struct xilly_endpoint {int* msgbuf_addr; int msg_buf_size; int msg_counter; int failed_messages; unsigned int num_channels; unsigned int idtlen; int fatal_error; scalar_t__ registers; int /*<<< orphan*/  msgbuf_dma_addr; TYPE_1__* ephw; int /*<<< orphan*/  dev; int /*<<< orphan*/  ep_wait; struct xilly_channel** channels; } ;
struct xilly_channel {unsigned int num_wr_buffers; unsigned int wr_fpga_buf_idx; unsigned int num_rd_buffers; unsigned int rd_fpga_buf_idx; unsigned int wr_host_buf_idx; int wr_ready; unsigned int wr_eof; int wr_hangup; int /*<<< orphan*/  wr_wait; int /*<<< orphan*/  wr_spinlock; int /*<<< orphan*/  wr_empty; int /*<<< orphan*/  wr_sleepy; int /*<<< orphan*/  wr_ready_wait; int /*<<< orphan*/  wr_supports_nonempty; int /*<<< orphan*/  rd_workitem; int /*<<< orphan*/  rd_synchronous; int /*<<< orphan*/  rd_wait; int /*<<< orphan*/  rd_spinlock; int /*<<< orphan*/  rd_full; TYPE_2__** wr_buffers; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {unsigned int end_offset; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* hw_sync_sgl_for_device ) (struct xilly_endpoint*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* hw_sync_sgl_for_cpu ) (struct xilly_endpoint*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  XILLYMSG_OPCODE_FATAL_ERROR 132 
#define  XILLYMSG_OPCODE_FIFOEOF 131 
#define  XILLYMSG_OPCODE_NONEMPTY 130 
#define  XILLYMSG_OPCODE_QUIESCEACK 129 
#define  XILLYMSG_OPCODE_RELEASEBUF 128 
 int /*<<< orphan*/  XILLY_RX_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int,int) ; 
 scalar_t__ fpga_msg_ctrl_reg ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  malformed_message (struct xilly_endpoint*,int*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct xilly_endpoint*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct xilly_endpoint*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct xilly_endpoint*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xillybus_wq ; 

irqreturn_t xillybus_isr(int irq, void *data)
{
	struct xilly_endpoint *ep = data;
	u32 *buf;
	unsigned int buf_size;
	int i;
	int opcode;
	unsigned int msg_channel, msg_bufno, msg_data, msg_dir;
	struct xilly_channel *channel;

	buf = ep->msgbuf_addr;
	buf_size = ep->msg_buf_size/sizeof(u32);

	ep->ephw->hw_sync_sgl_for_cpu(ep,
				      ep->msgbuf_dma_addr,
				      ep->msg_buf_size,
				      DMA_FROM_DEVICE);

	for (i = 0; i < buf_size; i += 2) {
		if (((buf[i+1] >> 28) & 0xf) != ep->msg_counter) {
			malformed_message(ep, &buf[i]);
			dev_warn(ep->dev,
				 "Sending a NACK on counter %x (instead of %x) on entry %d\n",
				 ((buf[i+1] >> 28) & 0xf),
				 ep->msg_counter,
				 i/2);

			if (++ep->failed_messages > 10) {
				dev_err(ep->dev,
					"Lost sync with interrupt messages. Stopping.\n");
			} else {
				ep->ephw->hw_sync_sgl_for_device(
					ep,
					ep->msgbuf_dma_addr,
					ep->msg_buf_size,
					DMA_FROM_DEVICE);

				iowrite32(0x01,  /* Message NACK */
					  ep->registers + fpga_msg_ctrl_reg);
			}
			return IRQ_HANDLED;
		} else if (buf[i] & (1 << 22)) /* Last message */
			break;
	}

	if (i >= buf_size) {
		dev_err(ep->dev, "Bad interrupt message. Stopping.\n");
		return IRQ_HANDLED;
	}

	buf_size = i + 2;

	for (i = 0; i < buf_size; i += 2) { /* Scan through messages */
		opcode = (buf[i] >> 24) & 0xff;

		msg_dir = buf[i] & 1;
		msg_channel = (buf[i] >> 1) & 0x7ff;
		msg_bufno = (buf[i] >> 12) & 0x3ff;
		msg_data = buf[i+1] & 0xfffffff;

		switch (opcode) {
		case XILLYMSG_OPCODE_RELEASEBUF:
			if ((msg_channel > ep->num_channels) ||
			    (msg_channel == 0)) {
				malformed_message(ep, &buf[i]);
				break;
			}

			channel = ep->channels[msg_channel];

			if (msg_dir) { /* Write channel */
				if (msg_bufno >= channel->num_wr_buffers) {
					malformed_message(ep, &buf[i]);
					break;
				}
				spin_lock(&channel->wr_spinlock);
				channel->wr_buffers[msg_bufno]->end_offset =
					msg_data;
				channel->wr_fpga_buf_idx = msg_bufno;
				channel->wr_empty = 0;
				channel->wr_sleepy = 0;
				spin_unlock(&channel->wr_spinlock);

				wake_up_interruptible(&channel->wr_wait);

			} else {
				/* Read channel */

				if (msg_bufno >= channel->num_rd_buffers) {
					malformed_message(ep, &buf[i]);
					break;
				}

				spin_lock(&channel->rd_spinlock);
				channel->rd_fpga_buf_idx = msg_bufno;
				channel->rd_full = 0;
				spin_unlock(&channel->rd_spinlock);

				wake_up_interruptible(&channel->rd_wait);
				if (!channel->rd_synchronous)
					queue_delayed_work(
						xillybus_wq,
						&channel->rd_workitem,
						XILLY_RX_TIMEOUT);
			}

			break;
		case XILLYMSG_OPCODE_NONEMPTY:
			if ((msg_channel > ep->num_channels) ||
			    (msg_channel == 0) || (!msg_dir) ||
			    !ep->channels[msg_channel]->wr_supports_nonempty) {
				malformed_message(ep, &buf[i]);
				break;
			}

			channel = ep->channels[msg_channel];

			if (msg_bufno >= channel->num_wr_buffers) {
				malformed_message(ep, &buf[i]);
				break;
			}
			spin_lock(&channel->wr_spinlock);
			if (msg_bufno == channel->wr_host_buf_idx)
				channel->wr_ready = 1;
			spin_unlock(&channel->wr_spinlock);

			wake_up_interruptible(&channel->wr_ready_wait);

			break;
		case XILLYMSG_OPCODE_QUIESCEACK:
			ep->idtlen = msg_data;
			wake_up_interruptible(&ep->ep_wait);

			break;
		case XILLYMSG_OPCODE_FIFOEOF:
			if ((msg_channel > ep->num_channels) ||
			    (msg_channel == 0) || (!msg_dir) ||
			    !ep->channels[msg_channel]->num_wr_buffers) {
				malformed_message(ep, &buf[i]);
				break;
			}
			channel = ep->channels[msg_channel];
			spin_lock(&channel->wr_spinlock);
			channel->wr_eof = msg_bufno;
			channel->wr_sleepy = 0;

			channel->wr_hangup = channel->wr_empty &&
				(channel->wr_host_buf_idx == msg_bufno);

			spin_unlock(&channel->wr_spinlock);

			wake_up_interruptible(&channel->wr_wait);

			break;
		case XILLYMSG_OPCODE_FATAL_ERROR:
			ep->fatal_error = 1;
			wake_up_interruptible(&ep->ep_wait); /* For select() */
			dev_err(ep->dev,
				"FPGA reported a fatal error. This means that the low-level communication with the device has failed. This hardware problem is most likely unrelated to Xillybus (neither kernel module nor FPGA core), but reports are still welcome. All I/O is aborted.\n");
			break;
		default:
			malformed_message(ep, &buf[i]);
			break;
		}
	}

	ep->ephw->hw_sync_sgl_for_device(ep,
					 ep->msgbuf_dma_addr,
					 ep->msg_buf_size,
					 DMA_FROM_DEVICE);

	ep->msg_counter = (ep->msg_counter + 1) & 0xf;
	ep->failed_messages = 0;
	iowrite32(0x03, ep->registers + fpga_msg_ctrl_reg); /* Message ACK */

	return IRQ_HANDLED;
}