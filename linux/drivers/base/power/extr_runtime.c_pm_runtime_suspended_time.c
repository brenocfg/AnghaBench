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
typedef  int /*<<< orphan*/  u64 ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpm_get_accounted_time (struct device*,int) ; 

u64 pm_runtime_suspended_time(struct device *dev)
{
	return rpm_get_accounted_time(dev, true);
}