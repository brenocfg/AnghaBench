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
struct TYPE_2__ {struct nvme_controller* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct nvme_controller {TYPE_1__ config_hook; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct nvme_controller* DEVICE2SOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_intrhook_establish (TYPE_1__*) ; 
 int nvme_ctrlr_construct (struct nvme_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_ctrlr_destruct (struct nvme_controller*,int /*<<< orphan*/ ) ; 
 int nvme_ctrlr_hw_reset (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_ctrlr_start_config_hook ; 

int
nvme_attach(device_t dev)
{
	struct nvme_controller	*ctrlr = DEVICE2SOFTC(dev);
	int			status;

	status = nvme_ctrlr_construct(ctrlr, dev);

	if (status != 0) {
		nvme_ctrlr_destruct(ctrlr, dev);
		return (status);
	}

	/*
	 * Reset controller twice to ensure we do a transition from cc.en==1 to
	 * cc.en==0.  This is because we don't really know what status the
	 * controller was left in when boot handed off to OS.  Linux doesn't do
	 * this, however. If we adopt that policy, see also nvme_ctrlr_resume().
	 */
	status = nvme_ctrlr_hw_reset(ctrlr);
	if (status != 0) {
		nvme_ctrlr_destruct(ctrlr, dev);
		return (status);
	}

	status = nvme_ctrlr_hw_reset(ctrlr);
	if (status != 0) {
		nvme_ctrlr_destruct(ctrlr, dev);
		return (status);
	}

	ctrlr->config_hook.ich_func = nvme_ctrlr_start_config_hook;
	ctrlr->config_hook.ich_arg = ctrlr;

	config_intrhook_establish(&ctrlr->config_hook);

	return (0);
}