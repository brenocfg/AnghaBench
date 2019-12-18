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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TAD_DC_TIMER ; 
 int /*<<< orphan*/  acpi_tad_status_read (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t dc_status_show(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	return acpi_tad_status_read(dev, buf, ACPI_TAD_DC_TIMER);
}