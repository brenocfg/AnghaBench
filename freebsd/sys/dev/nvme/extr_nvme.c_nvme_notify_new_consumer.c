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
struct nvme_controller {int dummy; } ;
struct nvme_consumer {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct nvme_controller* DEVICE2SOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ devclass_get_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_devclass ; 
 int /*<<< orphan*/  nvme_notify (struct nvme_consumer*,struct nvme_controller*) ; 

__attribute__((used)) static void
nvme_notify_new_consumer(struct nvme_consumer *cons)
{
	device_t		*devlist;
	struct nvme_controller	*ctrlr;
	int			dev_idx, devcount;

	if (devclass_get_devices(nvme_devclass, &devlist, &devcount))
		return;

	for (dev_idx = 0; dev_idx < devcount; dev_idx++) {
		ctrlr = DEVICE2SOFTC(devlist[dev_idx]);
		nvme_notify(cons, ctrlr);
	}

	free(devlist, M_TEMP);
}