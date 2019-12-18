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
 int /*<<< orphan*/  intmc ; 
 int /*<<< orphan*/  intms ; 
 int /*<<< orphan*/  nvme_ctrlr_poll (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_mmio_write_4 (struct nvme_controller*,int /*<<< orphan*/ ,int) ; 

void
nvme_ctrlr_intx_handler(void *arg)
{
	struct nvme_controller *ctrlr = arg;

	nvme_mmio_write_4(ctrlr, intms, 1);
	nvme_ctrlr_poll(ctrlr);
	nvme_mmio_write_4(ctrlr, intmc, 1);
}