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
typedef  size_t uint32_t ;
struct TYPE_3__ {scalar_t__ ver; scalar_t__ aerl; } ;
struct nvme_controller {int async_event_config; size_t num_aers; struct nvme_async_event_request* aer; TYPE_1__ cdata; } ;
struct TYPE_4__ {int cdw0; } ;
struct nvme_completion_poll_status {TYPE_2__ cpl; scalar_t__ done; } ;
struct nvme_async_event_request {int dummy; } ;

/* Variables and functions */
 int NVME_CRIT_WARN_ST_AVAILABLE_SPARE ; 
 int NVME_CRIT_WARN_ST_DEVICE_RELIABILITY ; 
 int NVME_CRIT_WARN_ST_READ_ONLY ; 
 int NVME_CRIT_WARN_ST_TEMPERATURE ; 
 int NVME_CRIT_WARN_ST_VOLATILE_MEMORY_BACKUP ; 
 int /*<<< orphan*/  NVME_FEAT_TEMPERATURE_THRESHOLD ; 
 int /*<<< orphan*/  NVME_MAX_ASYNC_EVENTS ; 
 scalar_t__ NVME_REV (int,int) ; 
 size_t min (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nvme_completion_is_error (TYPE_2__*) ; 
 int /*<<< orphan*/  nvme_completion_poll (struct nvme_completion_poll_status*) ; 
 int /*<<< orphan*/  nvme_completion_poll_cb ; 
 int /*<<< orphan*/  nvme_ctrlr_cmd_get_feature (struct nvme_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvme_completion_poll_status*) ; 
 int /*<<< orphan*/  nvme_ctrlr_cmd_set_async_event_config (struct nvme_controller*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_ctrlr_construct_and_submit_aer (struct nvme_controller*,struct nvme_async_event_request*) ; 
 int /*<<< orphan*/  nvme_printf (struct nvme_controller*,char*) ; 

__attribute__((used)) static void
nvme_ctrlr_configure_aer(struct nvme_controller *ctrlr)
{
	struct nvme_completion_poll_status	status;
	struct nvme_async_event_request		*aer;
	uint32_t				i;

	ctrlr->async_event_config = NVME_CRIT_WARN_ST_AVAILABLE_SPARE |
	    NVME_CRIT_WARN_ST_DEVICE_RELIABILITY |
	    NVME_CRIT_WARN_ST_READ_ONLY |
	    NVME_CRIT_WARN_ST_VOLATILE_MEMORY_BACKUP;
	if (ctrlr->cdata.ver >= NVME_REV(1, 2))
		ctrlr->async_event_config |= 0x300;

	status.done = 0;
	nvme_ctrlr_cmd_get_feature(ctrlr, NVME_FEAT_TEMPERATURE_THRESHOLD,
	    0, NULL, 0, nvme_completion_poll_cb, &status);
	nvme_completion_poll(&status);
	if (nvme_completion_is_error(&status.cpl) ||
	    (status.cpl.cdw0 & 0xFFFF) == 0xFFFF ||
	    (status.cpl.cdw0 & 0xFFFF) == 0x0000) {
		nvme_printf(ctrlr, "temperature threshold not supported\n");
	} else
		ctrlr->async_event_config |= NVME_CRIT_WARN_ST_TEMPERATURE;

	nvme_ctrlr_cmd_set_async_event_config(ctrlr,
	    ctrlr->async_event_config, NULL, NULL);

	/* aerl is a zero-based value, so we need to add 1 here. */
	ctrlr->num_aers = min(NVME_MAX_ASYNC_EVENTS, (ctrlr->cdata.aerl+1));

	for (i = 0; i < ctrlr->num_aers; i++) {
		aer = &ctrlr->aer[i];
		nvme_ctrlr_construct_and_submit_aer(ctrlr, aer);
	}
}