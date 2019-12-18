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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct dax_region {int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct dax_region* dev_get_drvdata (struct device*) ; 
 scalar_t__ resource_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 

__attribute__((used)) static ssize_t region_size_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct dax_region *dax_region = dev_get_drvdata(dev);

	return sprintf(buf, "%llu\n", (unsigned long long)
			resource_size(&dax_region->res));
}