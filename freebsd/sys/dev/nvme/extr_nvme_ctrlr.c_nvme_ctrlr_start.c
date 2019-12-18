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
typedef  int uint32_t ;
struct nvme_controller {int num_io_queues; int /*<<< orphan*/ * ioq; int /*<<< orphan*/  adminq; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_admin_qpair_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_ctrlr_configure_aer (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_ctrlr_configure_int_coalescing (struct nvme_controller*) ; 
 scalar_t__ nvme_ctrlr_construct_namespaces (struct nvme_controller*) ; 
 scalar_t__ nvme_ctrlr_create_qpairs (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_ctrlr_fail (struct nvme_controller*) ; 
 scalar_t__ nvme_ctrlr_identify (struct nvme_controller*) ; 
 scalar_t__ nvme_ctrlr_set_num_qpairs (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_io_qpair_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_qpair_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int,int) ; 

__attribute__((used)) static void
nvme_ctrlr_start(void *ctrlr_arg, bool resetting)
{
	struct nvme_controller *ctrlr = ctrlr_arg;
	uint32_t old_num_io_queues;
	int i;

	/*
	 * Only reset adminq here when we are restarting the
	 *  controller after a reset.  During initialization,
	 *  we have already submitted admin commands to get
	 *  the number of I/O queues supported, so cannot reset
	 *  the adminq again here.
	 */
	if (resetting)
		nvme_qpair_reset(&ctrlr->adminq);

	for (i = 0; i < ctrlr->num_io_queues; i++)
		nvme_qpair_reset(&ctrlr->ioq[i]);

	nvme_admin_qpair_enable(&ctrlr->adminq);

	if (nvme_ctrlr_identify(ctrlr) != 0) {
		nvme_ctrlr_fail(ctrlr);
		return;
	}

	/*
	 * The number of qpairs are determined during controller initialization,
	 *  including using NVMe SET_FEATURES/NUMBER_OF_QUEUES to determine the
	 *  HW limit.  We call SET_FEATURES again here so that it gets called
	 *  after any reset for controllers that depend on the driver to
	 *  explicit specify how many queues it will use.  This value should
	 *  never change between resets, so panic if somehow that does happen.
	 */
	if (resetting) {
		old_num_io_queues = ctrlr->num_io_queues;
		if (nvme_ctrlr_set_num_qpairs(ctrlr) != 0) {
			nvme_ctrlr_fail(ctrlr);
			return;
		}

		if (old_num_io_queues != ctrlr->num_io_queues) {
			panic("num_io_queues changed from %u to %u",
			      old_num_io_queues, ctrlr->num_io_queues);
		}
	}

	if (nvme_ctrlr_create_qpairs(ctrlr) != 0) {
		nvme_ctrlr_fail(ctrlr);
		return;
	}

	if (nvme_ctrlr_construct_namespaces(ctrlr) != 0) {
		nvme_ctrlr_fail(ctrlr);
		return;
	}

	nvme_ctrlr_configure_aer(ctrlr);
	nvme_ctrlr_configure_int_coalescing(ctrlr);

	for (i = 0; i < ctrlr->num_io_queues; i++)
		nvme_io_qpair_enable(&ctrlr->ioq[i]);
}