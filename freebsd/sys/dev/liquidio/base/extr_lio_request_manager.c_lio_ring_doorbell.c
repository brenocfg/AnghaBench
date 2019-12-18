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
struct octeon_device {int /*<<< orphan*/  status; } ;
struct lio_instr_queue {int /*<<< orphan*/  last_db_time; scalar_t__ fill_cnt; int /*<<< orphan*/  doorbell_reg; } ;

/* Variables and functions */
 scalar_t__ LIO_DEV_RUNNING ; 
 int /*<<< orphan*/  __compiler_membar () ; 
 scalar_t__ atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_write_csr32 (struct octeon_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ticks ; 

__attribute__((used)) static inline void
lio_ring_doorbell(struct octeon_device *oct, struct lio_instr_queue *iq)
{

	if (atomic_load_acq_int(&oct->status) == LIO_DEV_RUNNING) {
		lio_write_csr32(oct, iq->doorbell_reg, iq->fill_cnt);
		/* make sure doorbell write goes through */
		__compiler_membar();
		iq->fill_cnt = 0;
		iq->last_db_time = ticks;
		return;
	}
}