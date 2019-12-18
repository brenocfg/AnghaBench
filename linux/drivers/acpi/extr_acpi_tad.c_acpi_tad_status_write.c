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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int acpi_tad_clear_status (struct device*,int /*<<< orphan*/ ) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int acpi_tad_status_write(struct device *dev, const char *buf, u32 timer_id)
{
	int ret, value;

	ret = kstrtoint(buf, 0, &value);
	if (ret)
		return ret;

	if (value)
		return -EINVAL;

	return acpi_tad_clear_status(dev, timer_id);
}