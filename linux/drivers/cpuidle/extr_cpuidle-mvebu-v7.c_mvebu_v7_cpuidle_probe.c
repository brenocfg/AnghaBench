#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device_id {scalar_t__ driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  platform_data; } ;
struct platform_device {TYPE_1__ dev; struct platform_device_id* id_entry; } ;
struct cpuidle_driver {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int cpuidle_register (struct cpuidle_driver*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvebu_v7_cpu_suspend ; 

__attribute__((used)) static int mvebu_v7_cpuidle_probe(struct platform_device *pdev)
{
	const struct platform_device_id *id = pdev->id_entry;

	if (!id)
		return -EINVAL;

	mvebu_v7_cpu_suspend = pdev->dev.platform_data;

	return cpuidle_register((struct cpuidle_driver *)id->driver_data, NULL);
}