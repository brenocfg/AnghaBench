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
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAIT_CLOCKED ; 
 int /*<<< orphan*/  WAIT_UNCLOCKED ; 
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  cpuidle_lock ; 
 int /*<<< orphan*/  imx6_set_lpm (int /*<<< orphan*/ ) ; 
 scalar_t__ num_idle_cpus ; 
 scalar_t__ num_online_cpus () ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx6q_enter_wait(struct cpuidle_device *dev,
			    struct cpuidle_driver *drv, int index)
{
	raw_spin_lock(&cpuidle_lock);
	if (++num_idle_cpus == num_online_cpus())
		imx6_set_lpm(WAIT_UNCLOCKED);
	raw_spin_unlock(&cpuidle_lock);

	cpu_do_idle();

	raw_spin_lock(&cpuidle_lock);
	if (num_idle_cpus-- == num_online_cpus())
		imx6_set_lpm(WAIT_CLOCKED);
	raw_spin_unlock(&cpuidle_lock);

	return index;
}