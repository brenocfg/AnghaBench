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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct exynos_bus {int /*<<< orphan*/  devfreq; } ;

/* Variables and functions */
 struct exynos_bus* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devfreq_suspend_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_bus_shutdown(struct platform_device *pdev)
{
	struct exynos_bus *bus = dev_get_drvdata(&pdev->dev);

	devfreq_suspend_device(bus->devfreq);
}