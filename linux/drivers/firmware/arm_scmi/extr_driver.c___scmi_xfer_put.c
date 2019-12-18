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
struct scmi_xfers_info {int /*<<< orphan*/  xfer_lock; int /*<<< orphan*/  xfer_alloc_table; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq; } ;
struct scmi_xfer {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
__scmi_xfer_put(struct scmi_xfers_info *minfo, struct scmi_xfer *xfer)
{
	unsigned long flags;

	/*
	 * Keep the locked section as small as possible
	 * NOTE: we might escape with smp_mb and no lock here..
	 * but just be conservative and symmetric.
	 */
	spin_lock_irqsave(&minfo->xfer_lock, flags);
	clear_bit(xfer->hdr.seq, minfo->xfer_alloc_table);
	spin_unlock_irqrestore(&minfo->xfer_lock, flags);
}