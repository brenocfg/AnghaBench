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
typedef  int uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/ * ifp; } ;
struct TYPE_3__ {int (* msix_interrupt_handler ) (struct lio_ioq_vector*) ;} ;
struct octeon_device {TYPE_2__ props; int /*<<< orphan*/  tx_budget; int /*<<< orphan*/  rx_budget; struct lio_instr_queue** instr_queue; TYPE_1__ fn_list; struct lio_droq** droq; } ;
struct lio_ioq_vector {size_t droq_index; struct octeon_device* oct_dev; } ;
struct lio_instr_queue {int /*<<< orphan*/  enq_lock; int /*<<< orphan*/ * br; int /*<<< orphan*/  instr_pending; } ;
struct lio_droq {size_t q_no; int /*<<< orphan*/  droq_task; int /*<<< orphan*/  droq_taskqueue; } ;

/* Variables and functions */
 int LIO_MSIX_PI_INT ; 
 int LIO_MSIX_PO_INT ; 
 scalar_t__ atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drbr_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lio_droq_process_packets (struct octeon_device*,struct lio_droq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_enable_irq (struct lio_droq*,struct lio_instr_queue*) ; 
 int lio_flush_iq (struct octeon_device*,struct lio_instr_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_mq_start_locked (int /*<<< orphan*/ *,struct lio_instr_queue*) ; 
 scalar_t__ mtx_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct lio_ioq_vector*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lio_msix_intr_handler(void *vector)
{
	struct lio_ioq_vector	*ioq_vector = (struct lio_ioq_vector *)vector;
	struct octeon_device	*oct = ioq_vector->oct_dev;
	struct lio_droq		*droq = oct->droq[ioq_vector->droq_index];
	uint64_t		ret;

	ret = oct->fn_list.msix_interrupt_handler(ioq_vector);

	if ((ret & LIO_MSIX_PO_INT) || (ret & LIO_MSIX_PI_INT)) {
		struct lio_instr_queue *iq = oct->instr_queue[droq->q_no];
		int	reschedule, tx_done = 1;

		reschedule = lio_droq_process_packets(oct, droq, oct->rx_budget);

		if (atomic_load_acq_int(&iq->instr_pending))
			tx_done = lio_flush_iq(oct, iq, oct->tx_budget);

		if ((oct->props.ifp != NULL) && (iq->br != NULL)) {
			if (mtx_trylock(&iq->enq_lock)) {
				if (!drbr_empty(oct->props.ifp, iq->br))
					lio_mq_start_locked(oct->props.ifp,
							    iq);
				mtx_unlock(&iq->enq_lock);
			}
		}

		if (reschedule || !tx_done)
			taskqueue_enqueue(droq->droq_taskqueue, &droq->droq_task);
		else
			lio_enable_irq(droq, iq);
	}
}