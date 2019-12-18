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
struct vmbus_rxbr {int /*<<< orphan*/  rxbr_lock; int /*<<< orphan*/  rxbr_rindex; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int vmbus_rxbr_avail (struct vmbus_rxbr*) ; 
 int /*<<< orphan*/  vmbus_rxbr_copyfrom (struct vmbus_rxbr*,int /*<<< orphan*/ ,void*,int) ; 

int
vmbus_rxbr_peek(struct vmbus_rxbr *rbr, void *data, int dlen)
{
	mtx_lock_spin(&rbr->rxbr_lock);

	/*
	 * The requested data and the 64bits channel packet
	 * offset should be there at least.
	 */
	if (vmbus_rxbr_avail(rbr) < dlen + sizeof(uint64_t)) {
		mtx_unlock_spin(&rbr->rxbr_lock);
		return (EAGAIN);
	}
	vmbus_rxbr_copyfrom(rbr, rbr->rxbr_rindex, data, dlen);

	mtx_unlock_spin(&rbr->rxbr_lock);

	return (0);
}