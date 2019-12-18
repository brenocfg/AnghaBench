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
struct cpuidle_device {scalar_t__ poll_limit_ns; } ;

/* Variables and functions */

__attribute__((used)) static int haltpoll_enable_device(struct cpuidle_driver *drv,
				  struct cpuidle_device *dev)
{
	dev->poll_limit_ns = 0;

	return 0;
}