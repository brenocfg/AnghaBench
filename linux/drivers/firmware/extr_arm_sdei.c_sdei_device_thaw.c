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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_AP_ARM_SDEI_STARTING ; 
 int cpuhp_setup_state (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  sdei_cpuhp_down ; 
 int /*<<< orphan*/  sdei_cpuhp_up ; 
 int /*<<< orphan*/  sdei_mark_interface_broken () ; 
 int sdei_reregister_shared () ; 

__attribute__((used)) static int sdei_device_thaw(struct device *dev)
{
	int err;

	/* re-register shared events */
	err = sdei_reregister_shared();
	if (err) {
		pr_warn("Failed to re-register shared events...\n");
		sdei_mark_interface_broken();
		return err;
	}

	err = cpuhp_setup_state(CPUHP_AP_ARM_SDEI_STARTING, "SDEI",
				&sdei_cpuhp_up, &sdei_cpuhp_down);
	if (err)
		pr_warn("Failed to re-register CPU hotplug notifier...\n");

	return err;
}