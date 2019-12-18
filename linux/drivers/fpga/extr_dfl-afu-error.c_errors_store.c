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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int afu_port_err_clear (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtou64 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t errors_store(struct device *dev, struct device_attribute *attr,
			    const char *buff, size_t count)
{
	u64 value;
	int ret;

	if (kstrtou64(buff, 0, &value))
		return -EINVAL;

	ret = afu_port_err_clear(dev, value);

	return ret ? ret : count;
}