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
struct subsys_interface {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_cpu_prep ; 
 int /*<<< orphan*/  pm_cpu_sleep ; 
 int /*<<< orphan*/  s3c2412_cpu_suspend ; 
 int /*<<< orphan*/  s3c2412_pm_prepare ; 

__attribute__((used)) static int s3c2412_pm_add(struct device *dev, struct subsys_interface *sif)
{
	pm_cpu_prep = s3c2412_pm_prepare;
	pm_cpu_sleep = s3c2412_cpu_suspend;

	return 0;
}