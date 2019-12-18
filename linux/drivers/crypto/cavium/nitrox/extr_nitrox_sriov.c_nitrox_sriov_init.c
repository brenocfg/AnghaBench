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
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int nitrox_mbox_init (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_sriov_cleanup (struct nitrox_device*) ; 
 int nitrox_sriov_register_interupts (struct nitrox_device*) ; 

__attribute__((used)) static int nitrox_sriov_init(struct nitrox_device *ndev)
{
	int ret;

	/* register interrupts for PF in SR-IOV */
	ret = nitrox_sriov_register_interupts(ndev);
	if (ret)
		return ret;

	ret = nitrox_mbox_init(ndev);
	if (ret)
		goto sriov_init_fail;

	return 0;

sriov_init_fail:
	nitrox_sriov_cleanup(ndev);
	return ret;
}