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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct dev_dax {TYPE_1__* region; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 unsigned long long resource_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 
 struct dev_dax* to_dev_dax (struct device*) ; 

__attribute__((used)) static ssize_t size_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct dev_dax *dev_dax = to_dev_dax(dev);
	unsigned long long size = resource_size(&dev_dax->region->res);

	return sprintf(buf, "%llu\n", size);
}