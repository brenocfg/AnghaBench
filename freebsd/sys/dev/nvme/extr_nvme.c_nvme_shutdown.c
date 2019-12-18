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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct nvme_controller* DEVICE2SOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_ctrlr_shutdown (struct nvme_controller*) ; 

int
nvme_shutdown(device_t dev)
{
	struct nvme_controller	*ctrlr;

	ctrlr = DEVICE2SOFTC(dev);
	nvme_ctrlr_shutdown(ctrlr);

	return (0);
}