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
typedef  int /*<<< orphan*/  uint32_t ;
struct adf_etr_ring_data {int /*<<< orphan*/  lock; scalar_t__ tail; int /*<<< orphan*/  ring_number; TYPE_1__* bank; int /*<<< orphan*/  ring_size; int /*<<< orphan*/  msg_size; scalar_t__ base_addr; int /*<<< orphan*/  inflights; } ;
struct TYPE_2__ {int /*<<< orphan*/  bank_number; int /*<<< orphan*/  csr_addr; } ;

/* Variables and functions */
 scalar_t__ ADF_MAX_INFLIGHTS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ADF_MSG_SIZE_TO_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADF_RING_SIZE_MODULO (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  WRITE_CSR_RING_TAIL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ adf_modulo (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_add_return (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int adf_send_message(struct adf_etr_ring_data *ring, uint32_t *msg)
{
	if (atomic_add_return(1, ring->inflights) >
	    ADF_MAX_INFLIGHTS(ring->ring_size, ring->msg_size)) {
		atomic_dec(ring->inflights);
		return -EAGAIN;
	}
	spin_lock_bh(&ring->lock);
	memcpy((void *)((uintptr_t)ring->base_addr + ring->tail), msg,
	       ADF_MSG_SIZE_TO_BYTES(ring->msg_size));

	ring->tail = adf_modulo(ring->tail +
				ADF_MSG_SIZE_TO_BYTES(ring->msg_size),
				ADF_RING_SIZE_MODULO(ring->ring_size));
	WRITE_CSR_RING_TAIL(ring->bank->csr_addr, ring->bank->bank_number,
			    ring->ring_number, ring->tail);
	spin_unlock_bh(&ring->lock);
	return 0;
}