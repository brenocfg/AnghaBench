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
struct nvme_controller {int dummy; } ;
typedef  int /*<<< orphan*/  nvme_cb_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_FEAT_INTERRUPT_COALESCING ; 
 int /*<<< orphan*/  nvme_ctrlr_cmd_set_feature (struct nvme_controller*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nvme_printf (struct nvme_controller*,char*,int) ; 

void
nvme_ctrlr_cmd_set_interrupt_coalescing(struct nvme_controller *ctrlr,
    uint32_t microseconds, uint32_t threshold, nvme_cb_fn_t cb_fn, void *cb_arg)
{
	uint32_t cdw11;

	if ((microseconds/100) >= 0x100) {
		nvme_printf(ctrlr, "invalid coal time %d, disabling\n",
		    microseconds);
		microseconds = 0;
		threshold = 0;
	}

	if (threshold >= 0x100) {
		nvme_printf(ctrlr, "invalid threshold %d, disabling\n",
		    threshold);
		threshold = 0;
		microseconds = 0;
	}

	cdw11 = ((microseconds/100) << 8) | threshold;
	nvme_ctrlr_cmd_set_feature(ctrlr, NVME_FEAT_INTERRUPT_COALESCING, cdw11,
	    NULL, 0, cb_fn, cb_arg);
}