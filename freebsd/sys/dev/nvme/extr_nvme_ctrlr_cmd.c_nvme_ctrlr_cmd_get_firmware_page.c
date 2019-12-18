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
struct nvme_firmware_page {int dummy; } ;
struct nvme_controller {int dummy; } ;
typedef  int /*<<< orphan*/  nvme_cb_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_GLOBAL_NAMESPACE_TAG ; 
 int /*<<< orphan*/  NVME_LOG_FIRMWARE_SLOT ; 
 int /*<<< orphan*/  nvme_ctrlr_cmd_get_log_page (struct nvme_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvme_firmware_page*,int,int /*<<< orphan*/ ,void*) ; 

void
nvme_ctrlr_cmd_get_firmware_page(struct nvme_controller *ctrlr,
    struct nvme_firmware_page *payload, nvme_cb_fn_t cb_fn, void *cb_arg)
{

	nvme_ctrlr_cmd_get_log_page(ctrlr, NVME_LOG_FIRMWARE_SLOT, 
	    NVME_GLOBAL_NAMESPACE_TAG, payload, sizeof(*payload), cb_fn,
	    cb_arg);
}