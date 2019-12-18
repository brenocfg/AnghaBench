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
typedef  int /*<<< orphan*/  u8 ;
struct ti_sci_xfers_info {int /*<<< orphan*/  sem_xfer_count; int /*<<< orphan*/  xfer_lock; int /*<<< orphan*/  xfer_alloc_table; } ;
struct TYPE_2__ {scalar_t__ buf; } ;
struct ti_sci_xfer {TYPE_1__ tx_message; } ;
struct ti_sci_msg_hdr {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ti_sci_put_one_xfer(struct ti_sci_xfers_info *minfo,
				struct ti_sci_xfer *xfer)
{
	unsigned long flags;
	struct ti_sci_msg_hdr *hdr;
	u8 xfer_id;

	hdr = (struct ti_sci_msg_hdr *)xfer->tx_message.buf;
	xfer_id = hdr->seq;

	/*
	 * Keep the locked section as small as possible
	 * NOTE: we might escape with smp_mb and no lock here..
	 * but just be conservative and symmetric.
	 */
	spin_lock_irqsave(&minfo->xfer_lock, flags);
	clear_bit(xfer_id, minfo->xfer_alloc_table);
	spin_unlock_irqrestore(&minfo->xfer_lock, flags);

	/* Increment the count for the next user to get through */
	up(&minfo->sem_xfer_count);
}