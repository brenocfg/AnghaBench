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
typedef  int /*<<< orphan*/  uint32_t ;
struct nvme_controller {int dummy; } ;
typedef  int /*<<< orphan*/  nvme_cb_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_FEAT_ASYNC_EVENT_CONFIGURATION ; 
 int /*<<< orphan*/  nvme_ctrlr_cmd_set_feature (struct nvme_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void
nvme_ctrlr_cmd_set_async_event_config(struct nvme_controller *ctrlr,
    uint32_t state, nvme_cb_fn_t cb_fn, void *cb_arg)
{
	uint32_t cdw11;

	cdw11 = state;
	nvme_ctrlr_cmd_set_feature(ctrlr,
	    NVME_FEAT_ASYNC_EVENT_CONFIGURATION, cdw11, NULL, 0, cb_fn,
	    cb_arg);
}