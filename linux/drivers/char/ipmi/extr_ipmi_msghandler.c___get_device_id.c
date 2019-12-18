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
struct ipmi_smi {int /*<<< orphan*/ * null_user_handler; int /*<<< orphan*/  waitq; } ;
struct bmc_device {int dyn_id_set; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/ * bmc_device_id_handler ; 
 int send_get_device_id_cmd (struct ipmi_smi*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __get_device_id(struct ipmi_smi *intf, struct bmc_device *bmc)
{
	int rv;

	bmc->dyn_id_set = 2;

	intf->null_user_handler = bmc_device_id_handler;

	rv = send_get_device_id_cmd(intf);
	if (rv)
		return rv;

	wait_event(intf->waitq, bmc->dyn_id_set != 2);

	if (!bmc->dyn_id_set)
		rv = -EIO; /* Something went wrong in the fetch. */

	/* dyn_id_set makes the id data available. */
	smp_rmb();

	intf->null_user_handler = NULL;

	return rv;
}