#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mdts; } ;
struct nvme_controller {int min_page_size; TYPE_1__ cdata; int /*<<< orphan*/  max_xfer_size; } ;
struct nvme_completion_poll_status {int /*<<< orphan*/  cpl; scalar_t__ done; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvme_completion_is_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_completion_poll (struct nvme_completion_poll_status*) ; 
 int /*<<< orphan*/  nvme_completion_poll_cb ; 
 int /*<<< orphan*/  nvme_controller_data_swapbytes (TYPE_1__*) ; 
 int /*<<< orphan*/  nvme_ctrlr_cmd_identify_controller (struct nvme_controller*,TYPE_1__*,int /*<<< orphan*/ ,struct nvme_completion_poll_status*) ; 
 int /*<<< orphan*/  nvme_printf (struct nvme_controller*,char*) ; 

__attribute__((used)) static int
nvme_ctrlr_identify(struct nvme_controller *ctrlr)
{
	struct nvme_completion_poll_status	status;

	status.done = 0;
	nvme_ctrlr_cmd_identify_controller(ctrlr, &ctrlr->cdata,
	    nvme_completion_poll_cb, &status);
	nvme_completion_poll(&status);
	if (nvme_completion_is_error(&status.cpl)) {
		nvme_printf(ctrlr, "nvme_identify_controller failed!\n");
		return (ENXIO);
	}

	/* Convert data to host endian */
	nvme_controller_data_swapbytes(&ctrlr->cdata);

	/*
	 * Use MDTS to ensure our default max_xfer_size doesn't exceed what the
	 *  controller supports.
	 */
	if (ctrlr->cdata.mdts > 0)
		ctrlr->max_xfer_size = min(ctrlr->max_xfer_size,
		    ctrlr->min_page_size * (1 << (ctrlr->cdata.mdts)));

	return (0);
}