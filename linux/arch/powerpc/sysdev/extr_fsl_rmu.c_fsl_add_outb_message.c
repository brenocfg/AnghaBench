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
struct rio_tx_desc {int dport; int dattr; size_t dwcnt; int saddr; } ;
struct rio_mport {int index; } ;
struct rio_dev {int destid; } ;
struct TYPE_4__ {int tx_slot; int* phys_buffer; size_t size; scalar_t__* virt_buffer; scalar_t__ virt; } ;
struct fsl_rmu {TYPE_2__ msg_tx_ring; TYPE_1__* msg_regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  omr; } ;

/* Variables and functions */
 int EINVAL ; 
 struct fsl_rmu* GET_RMM_HANDLE (struct rio_mport*) ; 
 size_t RIO_MAX_MSG_SIZE ; 
 int RIO_MSG_OMR_MUI ; 
 int get_bitmask_order (size_t) ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_power_of_2 (size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,void*,size_t) ; 

int
fsl_add_outb_message(struct rio_mport *mport, struct rio_dev *rdev, int mbox,
			void *buffer, size_t len)
{
	struct fsl_rmu *rmu = GET_RMM_HANDLE(mport);
	u32 omr;
	struct rio_tx_desc *desc = (struct rio_tx_desc *)rmu->msg_tx_ring.virt
					+ rmu->msg_tx_ring.tx_slot;
	int ret = 0;

	pr_debug("RIO: fsl_add_outb_message(): destid %4.4x mbox %d buffer " \
		 "%p len %8.8zx\n", rdev->destid, mbox, buffer, len);
	if ((len < 8) || (len > RIO_MAX_MSG_SIZE)) {
		ret = -EINVAL;
		goto out;
	}

	/* Copy and clear rest of buffer */
	memcpy(rmu->msg_tx_ring.virt_buffer[rmu->msg_tx_ring.tx_slot], buffer,
			len);
	if (len < (RIO_MAX_MSG_SIZE - 4))
		memset(rmu->msg_tx_ring.virt_buffer[rmu->msg_tx_ring.tx_slot]
				+ len, 0, RIO_MAX_MSG_SIZE - len);

	/* Set mbox field for message, and set destid */
	desc->dport = (rdev->destid << 16) | (mbox & 0x3);

	/* Enable EOMI interrupt and priority */
	desc->dattr = 0x28000000 | ((mport->index) << 20);

	/* Set transfer size aligned to next power of 2 (in double words) */
	desc->dwcnt = is_power_of_2(len) ? len : 1 << get_bitmask_order(len);

	/* Set snooping and source buffer address */
	desc->saddr = 0x00000004
		| rmu->msg_tx_ring.phys_buffer[rmu->msg_tx_ring.tx_slot];

	/* Increment enqueue pointer */
	omr = in_be32(&rmu->msg_regs->omr);
	out_be32(&rmu->msg_regs->omr, omr | RIO_MSG_OMR_MUI);

	/* Go to next descriptor */
	if (++rmu->msg_tx_ring.tx_slot == rmu->msg_tx_ring.size)
		rmu->msg_tx_ring.tx_slot = 0;

out:
	return ret;
}