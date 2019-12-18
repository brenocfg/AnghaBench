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
struct nvme_health_information_page {int dummy; } ;
struct nvme_controller {int dummy; } ;
typedef  int /*<<< orphan*/  nvme_cb_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_LOG_HEALTH_INFORMATION ; 
 int /*<<< orphan*/  nvme_ctrlr_cmd_get_log_page (struct nvme_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvme_health_information_page*,int,int /*<<< orphan*/ ,void*) ; 

void
nvme_ctrlr_cmd_get_health_information_page(struct nvme_controller *ctrlr,
    uint32_t nsid, struct nvme_health_information_page *payload,
    nvme_cb_fn_t cb_fn, void *cb_arg)
{

	nvme_ctrlr_cmd_get_log_page(ctrlr, NVME_LOG_HEALTH_INFORMATION,
	    nsid, payload, sizeof(*payload), cb_fn, cb_arg);
}