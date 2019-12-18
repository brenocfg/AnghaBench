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
 scalar_t__ current_clr_polling_and_test () ; 
 int /*<<< orphan*/  default_idle () ; 
 int /*<<< orphan*/  local_irq_enable () ; 

__attribute__((used)) static int default_enter_idle(struct cpuidle_device *dev,
			      struct cpuidle_driver *drv, int index)
{
	if (current_clr_polling_and_test()) {
		local_irq_enable();
		return index;
	}
	default_idle();
	return index;
}