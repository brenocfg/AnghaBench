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
typedef  int uint16_t ;
struct nvme_qpair {int id; int cpu; size_t domain; int /*<<< orphan*/  res; } ;
struct nvme_controller {int dstrd; int max_hw_pend_io; int num_io_queues; size_t domain; int /*<<< orphan*/  dev; struct nvme_qpair* ioq; int /*<<< orphan*/  resource; } ;
struct TYPE_2__ {size_t pc_domain; } ;

/* Variables and functions */
 int CPU_FFS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_NVME ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NVME_CAP_LO_MQES (int /*<<< orphan*/ ) ; 
 int NVME_IO_ENTRIES ; 
 int NVME_IO_TRACKERS ; 
 int NVME_MAX_IO_TRACKERS ; 
 int /*<<< orphan*/  NVME_MIN_IO_TRACKERS ; 
 int QP (struct nvme_controller*,int) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  bus_bind_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * cpuset_domain ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * doorbell ; 
 struct nvme_qpair* malloc (int,int /*<<< orphan*/ ,int) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int nvme_mmio_offsetof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_mmio_read_4 (struct nvme_controller*,int /*<<< orphan*/ ) ; 
 int nvme_qpair_construct (struct nvme_qpair*,int,int,struct nvme_controller*) ; 
 TYPE_1__* pcpu_find (int) ; 
 int rman_get_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvme_ctrlr_construct_io_qpairs(struct nvme_controller *ctrlr)
{
	struct nvme_qpair	*qpair;
	uint32_t		cap_lo;
	uint16_t		mqes;
	int			c, error, i, n;
	int			num_entries, num_trackers, max_entries;

	/*
	 * NVMe spec sets a hard limit of 64K max entries, but devices may
	 * specify a smaller limit, so we need to check the MQES field in the
	 * capabilities register. We have to cap the number of entries to the
	 * current stride allows for in BAR 0/1, otherwise the remainder entries
	 * are inaccessable. MQES should reflect this, and this is just a
	 * fail-safe.
	 */
	max_entries =
	    (rman_get_size(ctrlr->resource) - nvme_mmio_offsetof(doorbell[0])) /
	    (1 << (ctrlr->dstrd + 1));
	num_entries = NVME_IO_ENTRIES;
	TUNABLE_INT_FETCH("hw.nvme.io_entries", &num_entries);
	cap_lo = nvme_mmio_read_4(ctrlr, cap_lo);
	mqes = NVME_CAP_LO_MQES(cap_lo);
	num_entries = min(num_entries, mqes + 1);
	num_entries = min(num_entries, max_entries);

	num_trackers = NVME_IO_TRACKERS;
	TUNABLE_INT_FETCH("hw.nvme.io_trackers", &num_trackers);

	num_trackers = max(num_trackers, NVME_MIN_IO_TRACKERS);
	num_trackers = min(num_trackers, NVME_MAX_IO_TRACKERS);
	/*
	 * No need to have more trackers than entries in the submit queue.  Note
	 * also that for a queue size of N, we can only have (N-1) commands
	 * outstanding, hence the "-1" here.
	 */
	num_trackers = min(num_trackers, (num_entries-1));

	/*
	 * Our best estimate for the maximum number of I/Os that we should
	 * normally have in flight at one time. This should be viewed as a hint,
	 * not a hard limit and will need to be revisited when the upper layers
	 * of the storage system grows multi-queue support.
	 */
	ctrlr->max_hw_pend_io = num_trackers * ctrlr->num_io_queues * 3 / 4;

	ctrlr->ioq = malloc(ctrlr->num_io_queues * sizeof(struct nvme_qpair),
	    M_NVME, M_ZERO | M_WAITOK);

	for (i = c = n = 0; i < ctrlr->num_io_queues; i++, c += n) {
		qpair = &ctrlr->ioq[i];

		/*
		 * Admin queue has ID=0. IO queues start at ID=1 -
		 *  hence the 'i+1' here.
		 */
		qpair->id = i + 1;
		if (ctrlr->num_io_queues > 1) {
			/* Find number of CPUs served by this queue. */
			for (n = 1; QP(ctrlr, c + n) == i; n++)
				;
			/* Shuffle multiple NVMe devices between CPUs. */
			qpair->cpu = c + (device_get_unit(ctrlr->dev)+n/2) % n;
			qpair->domain = pcpu_find(qpair->cpu)->pc_domain;
		} else {
			qpair->cpu = CPU_FFS(&cpuset_domain[ctrlr->domain]) - 1;
			qpair->domain = ctrlr->domain;
		}

		/*
		 * For I/O queues, use the controller-wide max_xfer_size
		 *  calculated in nvme_attach().
		 */
		error = nvme_qpair_construct(qpair, num_entries, num_trackers,
		    ctrlr);
		if (error)
			return (error);

		/*
		 * Do not bother binding interrupts if we only have one I/O
		 *  interrupt thread for this controller.
		 */
		if (ctrlr->num_io_queues > 1)
			bus_bind_intr(ctrlr->dev, qpair->res, qpair->cpu);
	}

	return (0);
}