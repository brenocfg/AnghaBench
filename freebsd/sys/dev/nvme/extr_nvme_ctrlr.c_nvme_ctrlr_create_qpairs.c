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
struct nvme_qpair {int /*<<< orphan*/  ctrlr; } ;
struct nvme_controller {int num_io_queues; struct nvme_qpair* ioq; } ;
struct nvme_completion_poll_status {int /*<<< orphan*/  cpl; scalar_t__ done; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ nvme_completion_is_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_completion_poll (struct nvme_completion_poll_status*) ; 
 int /*<<< orphan*/  nvme_completion_poll_cb ; 
 int /*<<< orphan*/  nvme_ctrlr_cmd_create_io_cq (struct nvme_controller*,struct nvme_qpair*,int /*<<< orphan*/ ,struct nvme_completion_poll_status*) ; 
 int /*<<< orphan*/  nvme_ctrlr_cmd_create_io_sq (int /*<<< orphan*/ ,struct nvme_qpair*,int /*<<< orphan*/ ,struct nvme_completion_poll_status*) ; 
 int /*<<< orphan*/  nvme_printf (struct nvme_controller*,char*) ; 

__attribute__((used)) static int
nvme_ctrlr_create_qpairs(struct nvme_controller *ctrlr)
{
	struct nvme_completion_poll_status	status;
	struct nvme_qpair			*qpair;
	int					i;

	for (i = 0; i < ctrlr->num_io_queues; i++) {
		qpair = &ctrlr->ioq[i];

		status.done = 0;
		nvme_ctrlr_cmd_create_io_cq(ctrlr, qpair,
		    nvme_completion_poll_cb, &status);
		nvme_completion_poll(&status);
		if (nvme_completion_is_error(&status.cpl)) {
			nvme_printf(ctrlr, "nvme_create_io_cq failed!\n");
			return (ENXIO);
		}

		status.done = 0;
		nvme_ctrlr_cmd_create_io_sq(qpair->ctrlr, qpair,
		    nvme_completion_poll_cb, &status);
		nvme_completion_poll(&status);
		if (nvme_completion_is_error(&status.cpl)) {
			nvme_printf(ctrlr, "nvme_create_io_sq failed!\n");
			return (ENXIO);
		}
	}

	return (0);
}