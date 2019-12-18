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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct vmbus_rxbr {scalar_t__ rxbr_dsize; scalar_t__ rxbr_rindex; int /*<<< orphan*/  rxbr_lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ VMBUS_BR_IDXINC (scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  __compiler_membar () ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 scalar_t__ vmbus_rxbr_avail (struct vmbus_rxbr*) ; 
 scalar_t__ vmbus_rxbr_copyfrom (struct vmbus_rxbr*,scalar_t__,void*,int) ; 

int
vmbus_rxbr_read(struct vmbus_rxbr *rbr, void *data, int dlen, uint32_t skip)
{
	uint32_t rindex, br_dsize = rbr->rxbr_dsize;

	KASSERT(dlen + skip > 0, ("invalid dlen %d, offset %u", dlen, skip));

	mtx_lock_spin(&rbr->rxbr_lock);

	if (vmbus_rxbr_avail(rbr) < dlen + skip + sizeof(uint64_t)) {
		mtx_unlock_spin(&rbr->rxbr_lock);
		return (EAGAIN);
	}

	/*
	 * Copy channel packet from RX bufring.
	 */
	rindex = VMBUS_BR_IDXINC(rbr->rxbr_rindex, skip, br_dsize);
	rindex = vmbus_rxbr_copyfrom(rbr, rindex, data, dlen);

	/*
	 * Discard this channel packet's 64bits offset, which is useless to us.
	 */
	rindex = VMBUS_BR_IDXINC(rindex, sizeof(uint64_t), br_dsize);

	/*
	 * Update the read index _after_ the channel packet is fetched.
	 */
	__compiler_membar();
	rbr->rxbr_rindex = rindex;

	mtx_unlock_spin(&rbr->rxbr_lock);

	return (0);
}