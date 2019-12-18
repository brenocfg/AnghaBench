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
struct nvme_tracker {int dummy; } ;
struct nvme_qpair {size_t cq_head; size_t num_entries; int phase; int /*<<< orphan*/  cq_hdbl_off; TYPE_1__* ctrlr; struct nvme_completion* cpl; int /*<<< orphan*/  sq_head; struct nvme_tracker** act_tr; int /*<<< orphan*/  queuemem_map; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  is_enabled; int /*<<< orphan*/  num_intr_handler_calls; } ;
struct nvme_completion {size_t cid; int /*<<< orphan*/  sqhd; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus_handle; int /*<<< orphan*/  bus_tag; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  ERROR_PRINT_ALL ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int NVME_STATUS_GET_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SCHEDULER_STOPPED () ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  atomic_store_rel_int (size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ dumping ; 
 int /*<<< orphan*/  nvme_completion_swapbytes (struct nvme_completion*) ; 
 int /*<<< orphan*/  nvme_dump_completion (struct nvme_completion*) ; 
 int /*<<< orphan*/  nvme_printf (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  nvme_qpair_complete_tracker (struct nvme_qpair*,struct nvme_tracker*,struct nvme_completion*,int /*<<< orphan*/ ) ; 

bool
nvme_qpair_process_completions(struct nvme_qpair *qpair)
{
	struct nvme_tracker	*tr;
	struct nvme_completion	cpl;
	int done = 0;
	bool in_panic = dumping || SCHEDULER_STOPPED();

	qpair->num_intr_handler_calls++;

	/*
	 * qpair is not enabled, likely because a controller reset is is in
	 * progress.  Ignore the interrupt - any I/O that was associated with
	 * this interrupt will get retried when the reset is complete.
	 */
	if (!qpair->is_enabled)
		return (false);

	/*
	 * A panic can stop the CPU this routine is running on at any point.  If
	 * we're called during a panic, complete the sq_head wrap protocol for
	 * the case where we are interrupted just after the increment at 1
	 * below, but before we can reset cq_head to zero at 2. Also cope with
	 * the case where we do the zero at 2, but may or may not have done the
	 * phase adjustment at step 3. The panic machinery flushes all pending
	 * memory writes, so we can make these strong ordering assumptions
	 * that would otherwise be unwise if we were racing in real time.
	 */
	if (__predict_false(in_panic)) {
		if (qpair->cq_head == qpair->num_entries) {
			/*
			 * Here we know that we need to zero cq_head and then negate
			 * the phase, which hasn't been assigned if cq_head isn't
			 * zero due to the atomic_store_rel.
			 */
			qpair->cq_head = 0;
			qpair->phase = !qpair->phase;
		} else if (qpair->cq_head == 0) {
			/*
			 * In this case, we know that the assignment at 2
			 * happened below, but we don't know if it 3 happened or
			 * not. To do this, we look at the last completion
			 * entry and set the phase to the opposite phase
			 * that it has. This gets us back in sync
			 */
			cpl = qpair->cpl[qpair->num_entries - 1];
			nvme_completion_swapbytes(&cpl);
			qpair->phase = !NVME_STATUS_GET_P(cpl.status);
		}
	}

	bus_dmamap_sync(qpair->dma_tag, qpair->queuemem_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	while (1) {
		cpl = qpair->cpl[qpair->cq_head];

		/* Convert to host endian */
		nvme_completion_swapbytes(&cpl);

		if (NVME_STATUS_GET_P(cpl.status) != qpair->phase)
			break;

		tr = qpair->act_tr[cpl.cid];

		if (tr != NULL) {
			nvme_qpair_complete_tracker(qpair, tr, &cpl, ERROR_PRINT_ALL);
			qpair->sq_head = cpl.sqhd;
			done++;
		} else if (!in_panic) {
			/*
			 * A missing tracker is normally an error.  However, a
			 * panic can stop the CPU this routine is running on
			 * after completing an I/O but before updating
			 * qpair->cq_head at 1 below.  Later, we re-enter this
			 * routine to poll I/O associated with the kernel
			 * dump. We find that the tr has been set to null before
			 * calling the completion routine.  If it hasn't
			 * completed (or it triggers a panic), then '1' below
			 * won't have updated cq_head. Rather than panic again,
			 * ignore this condition because it's not unexpected.
			 */
			nvme_printf(qpair->ctrlr,
			    "cpl does not map to outstanding cmd\n");
			/* nvme_dump_completion expects device endianess */
			nvme_dump_completion(&qpair->cpl[qpair->cq_head]);
			KASSERT(0, ("received completion for unknown cmd"));
		}

		/*
		 * There's a number of races with the following (see above) when
		 * the system panics. We compensate for each one of them by
		 * using the atomic store to force strong ordering (at least when
		 * viewed in the aftermath of a panic).
		 */
		if (++qpair->cq_head == qpair->num_entries) {		/* 1 */
			atomic_store_rel_int(&qpair->cq_head, 0);	/* 2 */
			qpair->phase = !qpair->phase;			/* 3 */
		}

		bus_space_write_4(qpair->ctrlr->bus_tag, qpair->ctrlr->bus_handle,
		    qpair->cq_hdbl_off, qpair->cq_head);
	}
	return (done != 0);
}