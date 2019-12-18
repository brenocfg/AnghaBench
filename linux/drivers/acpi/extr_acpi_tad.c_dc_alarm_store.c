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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TAD_DC_TIMER ; 
 int acpi_tad_alarm_write (struct device*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t dc_alarm_store(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	int ret = acpi_tad_alarm_write(dev, buf, ACPI_TAD_DC_TIMER);

	return ret ? ret : count;
}