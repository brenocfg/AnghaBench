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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int /*<<< orphan*/  iosf_mbi_pmic_bus_access_notifier ; 
 int /*<<< orphan*/  iosf_mbi_punit_acquire () ; 
 int /*<<< orphan*/  iosf_mbi_punit_release () ; 

int iosf_mbi_register_pmic_bus_access_notifier(struct notifier_block *nb)
{
	int ret;

	/* Wait for the bus to go inactive before registering */
	iosf_mbi_punit_acquire();
	ret = blocking_notifier_chain_register(
				&iosf_mbi_pmic_bus_access_notifier, nb);
	iosf_mbi_punit_release();

	return ret;
}