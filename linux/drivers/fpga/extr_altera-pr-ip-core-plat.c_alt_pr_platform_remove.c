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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  alt_pr_unregister (struct device*) ; 

__attribute__((used)) static int alt_pr_platform_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	alt_pr_unregister(dev);

	return 0;
}