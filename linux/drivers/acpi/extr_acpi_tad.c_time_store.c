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
struct acpi_tad_rt {int year; int month; int day; int hour; int minute; int second; int tz; int daylight; int /*<<< orphan*/  padding; scalar_t__ msec; scalar_t__ valid; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* acpi_tad_rt_next_field (char*,int*) ; 
 int acpi_tad_set_real_time (struct device*,struct acpi_tad_rt*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmemdup_nul (char const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoint (char*,int,int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t time_store(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct acpi_tad_rt rt;
	char *str, *s;
	int val, ret = -ENODATA;

	str = kmemdup_nul(buf, count, GFP_KERNEL);
	if (!str)
		return -ENOMEM;

	s = acpi_tad_rt_next_field(str, &val);
	if (!s)
		goto out_free;

	rt.year = val;

	s = acpi_tad_rt_next_field(s, &val);
	if (!s)
		goto out_free;

	rt.month = val;

	s = acpi_tad_rt_next_field(s, &val);
	if (!s)
		goto out_free;

	rt.day = val;

	s = acpi_tad_rt_next_field(s, &val);
	if (!s)
		goto out_free;

	rt.hour = val;

	s = acpi_tad_rt_next_field(s, &val);
	if (!s)
		goto out_free;

	rt.minute = val;

	s = acpi_tad_rt_next_field(s, &val);
	if (!s)
		goto out_free;

	rt.second = val;

	s = acpi_tad_rt_next_field(s, &val);
	if (!s)
		goto out_free;

	rt.tz = val;

	if (kstrtoint(s, 10, &val))
		goto out_free;

	rt.daylight = val;

	rt.valid = 0;
	rt.msec = 0;
	memset(rt.padding, 0, 3);

	ret = acpi_tad_set_real_time(dev, &rt);

out_free:
	kfree(str);
	return ret ? ret : count;
}