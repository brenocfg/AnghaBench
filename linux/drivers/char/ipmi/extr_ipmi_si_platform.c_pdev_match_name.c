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
struct platform_device {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int pdev_match_name(struct device *dev, const void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	const char *name = data;

	return strcmp(pdev->name, name) == 0;
}