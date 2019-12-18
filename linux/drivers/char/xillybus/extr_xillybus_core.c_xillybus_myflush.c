#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xilly_channel {int rd_host_buf_idx; int num_rd_buffers; int rd_host_buf_pos; int log2_element_size; int* rd_leftovers; int rd_full; int rd_fpga_buf_idx; int chan_num; TYPE_3__* endpoint; int /*<<< orphan*/  rd_mutex; int /*<<< orphan*/  rd_wait; int /*<<< orphan*/  rd_spinlock; int /*<<< orphan*/  rd_buf_size; TYPE_2__** rd_buffers; int /*<<< orphan*/  rd_ref_count; } ;
struct TYPE_6__ {scalar_t__ fatal_error; int /*<<< orphan*/  dev; int /*<<< orphan*/  register_mutex; scalar_t__ registers; TYPE_1__* ephw; } ;
struct TYPE_5__ {unsigned char* addr; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* hw_sync_sgl_for_device ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINTR ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fpga_buf_ctrl_reg ; 
 scalar_t__ fpga_buf_offset_reg ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 scalar_t__ wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,long) ; 

__attribute__((used)) static int xillybus_myflush(struct xilly_channel *channel, long timeout)
{
	int rc;
	unsigned long flags;

	int end_offset_plus1;
	int bufidx, bufidx_minus1;
	int i;
	int empty;
	int new_rd_host_buf_pos;

	if (channel->endpoint->fatal_error)
		return -EIO;
	rc = mutex_lock_interruptible(&channel->rd_mutex);
	if (rc)
		return rc;

	/*
	 * Don't flush a closed channel. This can happen when the work queued
	 * autoflush thread fires off after the file has closed. This is not
	 * an error, just something to dismiss.
	 */

	if (!channel->rd_ref_count)
		goto done;

	bufidx = channel->rd_host_buf_idx;

	bufidx_minus1 = (bufidx == 0) ?
		channel->num_rd_buffers - 1 :
		bufidx - 1;

	end_offset_plus1 = channel->rd_host_buf_pos >>
		channel->log2_element_size;

	new_rd_host_buf_pos = channel->rd_host_buf_pos -
		(end_offset_plus1 << channel->log2_element_size);

	/* Submit the current buffer if it's nonempty */
	if (end_offset_plus1) {
		unsigned char *tail = channel->rd_buffers[bufidx]->addr +
			(end_offset_plus1 << channel->log2_element_size);

		/* Copy  unflushed data, so we can put it in next buffer */
		for (i = 0; i < new_rd_host_buf_pos; i++)
			channel->rd_leftovers[i] = *tail++;

		spin_lock_irqsave(&channel->rd_spinlock, flags);

		/* Autoflush only if a single buffer is occupied */

		if ((timeout < 0) &&
		    (channel->rd_full ||
		     (bufidx_minus1 != channel->rd_fpga_buf_idx))) {
			spin_unlock_irqrestore(&channel->rd_spinlock, flags);
			/*
			 * A new work item may be queued by the ISR exactly
			 * now, since the execution of a work item allows the
			 * queuing of a new one while it's running.
			 */
			goto done;
		}

		/* The 4th element is never needed for data, so it's a flag */
		channel->rd_leftovers[3] = (new_rd_host_buf_pos != 0);

		/* Set up rd_full to reflect a certain moment's state */

		if (bufidx == channel->rd_fpga_buf_idx)
			channel->rd_full = 1;
		spin_unlock_irqrestore(&channel->rd_spinlock, flags);

		if (bufidx >= (channel->num_rd_buffers - 1))
			channel->rd_host_buf_idx = 0;
		else
			channel->rd_host_buf_idx++;

		channel->endpoint->ephw->hw_sync_sgl_for_device(
			channel->endpoint,
			channel->rd_buffers[bufidx]->dma_addr,
			channel->rd_buf_size,
			DMA_TO_DEVICE);

		mutex_lock(&channel->endpoint->register_mutex);

		iowrite32(end_offset_plus1 - 1,
			  channel->endpoint->registers + fpga_buf_offset_reg);

		iowrite32((channel->chan_num << 1) | /* Channel ID */
			  (2 << 24) |  /* Opcode 2, submit buffer */
			  (bufidx << 12),
			  channel->endpoint->registers + fpga_buf_ctrl_reg);

		mutex_unlock(&channel->endpoint->register_mutex);
	} else if (bufidx == 0) {
		bufidx = channel->num_rd_buffers - 1;
	} else {
		bufidx--;
	}

	channel->rd_host_buf_pos = new_rd_host_buf_pos;

	if (timeout < 0)
		goto done; /* Autoflush */

	/*
	 * bufidx is now the last buffer written to (or equal to
	 * rd_fpga_buf_idx if buffer was never written to), and
	 * channel->rd_host_buf_idx the one after it.
	 *
	 * If bufidx == channel->rd_fpga_buf_idx we're either empty or full.
	 */

	while (1) { /* Loop waiting for draining of buffers */
		spin_lock_irqsave(&channel->rd_spinlock, flags);

		if (bufidx != channel->rd_fpga_buf_idx)
			channel->rd_full = 1; /*
					       * Not really full,
					       * but needs waiting.
					       */

		empty = !channel->rd_full;

		spin_unlock_irqrestore(&channel->rd_spinlock, flags);

		if (empty)
			break;

		/*
		 * Indefinite sleep with mutex taken. With data waiting for
		 * flushing user should not be surprised if open() for write
		 * sleeps.
		 */
		if (timeout == 0)
			wait_event_interruptible(channel->rd_wait,
						 (!channel->rd_full));

		else if (wait_event_interruptible_timeout(
				 channel->rd_wait,
				 (!channel->rd_full),
				 timeout) == 0) {
			dev_warn(channel->endpoint->dev,
				 "Timed out while flushing. Output data may be lost.\n");

			rc = -ETIMEDOUT;
			break;
		}

		if (channel->rd_full) {
			rc = -EINTR;
			break;
		}
	}

done:
	mutex_unlock(&channel->rd_mutex);

	if (channel->endpoint->fatal_error)
		return -EIO;

	return rc;
}