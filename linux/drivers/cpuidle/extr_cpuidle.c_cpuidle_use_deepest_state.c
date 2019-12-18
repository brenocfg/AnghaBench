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
struct cpuidle_device {int use_deepest_state; } ;

/* Variables and functions */
 struct cpuidle_device* cpuidle_get_device () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

void cpuidle_use_deepest_state(bool enable)
{
	struct cpuidle_device *dev;

	preempt_disable();
	dev = cpuidle_get_device();
	if (dev)
		dev->use_deepest_state = enable;
	preempt_enable();
}