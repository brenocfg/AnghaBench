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
struct cpuidle_device {int last_state_idx; int /*<<< orphan*/  last_residency; } ;

/* Variables and functions */
 int /*<<< orphan*/  adjust_poll_limit (struct cpuidle_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void haltpoll_reflect(struct cpuidle_device *dev, int index)
{
	dev->last_state_idx = index;

	if (index != 0)
		adjust_poll_limit(dev, dev->last_residency);
}