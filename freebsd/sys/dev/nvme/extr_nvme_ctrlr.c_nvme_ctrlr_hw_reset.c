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

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int nvme_ctrlr_disable (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_ctrlr_disable_qpairs (struct nvme_controller*) ; 
 int nvme_ctrlr_enable (struct nvme_controller*) ; 

int
nvme_ctrlr_hw_reset(struct nvme_controller *ctrlr)
{
	int err;

	nvme_ctrlr_disable_qpairs(ctrlr);

	DELAY(100*1000);

	err = nvme_ctrlr_disable(ctrlr);
	if (err != 0)
		return err;
	return (nvme_ctrlr_enable(ctrlr));
}