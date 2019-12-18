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
typedef  size_t uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/ * ifp; } ;
struct octeon_device {TYPE_1__ props; struct lio_instr_queue** instr_queue; } ;
struct lio_instr_queue {size_t last_db_time; int /*<<< orphan*/  enq_lock; int /*<<< orphan*/ * br; int /*<<< orphan*/  db_timeout; int /*<<< orphan*/  instr_pending; } ;

/* Variables and functions */
 scalar_t__ atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbr_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_check_timeout (size_t,size_t) ; 
 int /*<<< orphan*/  lio_enable_irq (int /*<<< orphan*/ *,struct lio_instr_queue*) ; 
 int /*<<< orphan*/  lio_flush_iq (struct octeon_device*,struct lio_instr_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_mq_start_locked (int /*<<< orphan*/ *,struct lio_instr_queue*) ; 
 size_t lio_ms_to_ticks (int /*<<< orphan*/ ) ; 
 scalar_t__ mtx_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 size_t ticks ; 

__attribute__((used)) static void
__lio_check_db_timeout(struct octeon_device *oct, uint64_t iq_no)
{
	struct lio_instr_queue	*iq;
	uint64_t		next_time;

	if (oct == NULL)
		return;

	iq = oct->instr_queue[iq_no];
	if (iq == NULL)
		return;

	if (atomic_load_acq_int(&iq->instr_pending)) {
		/* If ticks - last_db_time < db_timeout do nothing  */
		next_time = iq->last_db_time + lio_ms_to_ticks(iq->db_timeout);
		if (!lio_check_timeout(ticks, next_time))
			return;

		iq->last_db_time = ticks;

		/* Flush the instruction queue */
		lio_flush_iq(oct, iq, 0);

		lio_enable_irq(NULL, iq);
	}

	if (oct->props.ifp != NULL && iq->br != NULL) {
		if (mtx_trylock(&iq->enq_lock)) {
			if (!drbr_empty(oct->props.ifp, iq->br))
				lio_mq_start_locked(oct->props.ifp, iq);

			mtx_unlock(&iq->enq_lock);
		}
	}
}