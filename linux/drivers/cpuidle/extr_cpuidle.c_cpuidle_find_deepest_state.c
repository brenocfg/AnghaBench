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
 int /*<<< orphan*/  UINT_MAX ; 
 int find_deepest_state (struct cpuidle_driver*,struct cpuidle_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int cpuidle_find_deepest_state(struct cpuidle_driver *drv,
			       struct cpuidle_device *dev)
{
	return find_deepest_state(drv, dev, UINT_MAX, 0, false);
}