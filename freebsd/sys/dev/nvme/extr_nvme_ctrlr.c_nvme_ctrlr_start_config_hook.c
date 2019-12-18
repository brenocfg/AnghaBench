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
struct nvme_controller {int is_initialized; int /*<<< orphan*/  config_hook; int /*<<< orphan*/  adminq; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_admin_qpair_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ nvme_ctrlr_construct_io_qpairs (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_ctrlr_fail (struct nvme_controller*) ; 
 scalar_t__ nvme_ctrlr_set_num_qpairs (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_ctrlr_start (struct nvme_controller*,int) ; 
 int /*<<< orphan*/  nvme_notify_new_controller (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_qpair_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_sysctl_initialize_ctrlr (struct nvme_controller*) ; 

void
nvme_ctrlr_start_config_hook(void *arg)
{
	struct nvme_controller *ctrlr = arg;

	nvme_qpair_reset(&ctrlr->adminq);
	nvme_admin_qpair_enable(&ctrlr->adminq);

	if (nvme_ctrlr_set_num_qpairs(ctrlr) == 0 &&
	    nvme_ctrlr_construct_io_qpairs(ctrlr) == 0)
		nvme_ctrlr_start(ctrlr, false);
	else
		nvme_ctrlr_fail(ctrlr);

	nvme_sysctl_initialize_ctrlr(ctrlr);
	config_intrhook_disestablish(&ctrlr->config_hook);

	ctrlr->is_initialized = 1;
	nvme_notify_new_controller(ctrlr);
}