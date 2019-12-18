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

/* Variables and functions */
 int /*<<< orphan*/  RAC_ENABLED ; 
 int /*<<< orphan*/  RAC_SUSPENDED ; 
 int /*<<< orphan*/  __b15_rac_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b15_rac_flags ; 
 int /*<<< orphan*/  rac_config0_reg ; 
 int /*<<< orphan*/  rac_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int b15_rac_dead_cpu(unsigned int cpu)
{
	/* During kexec/reboot, the RAC is disabled via the reboot notifier
	 * return early here.
	 */
	if (test_bit(RAC_SUSPENDED, &b15_rac_flags))
		return 0;

	spin_lock(&rac_lock);

	/* And enable it */
	__b15_rac_enable(rac_config0_reg);
	__set_bit(RAC_ENABLED, &b15_rac_flags);

	spin_unlock(&rac_lock);

	return 0;
}