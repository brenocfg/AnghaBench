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
struct fw_unit {scalar_t__ directory; } ;
struct fw_device {scalar_t__ config_rom; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct fw_device* fw_device (int /*<<< orphan*/ ) ; 
 struct fw_unit* fw_unit (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t rom_index_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct fw_device *device = fw_device(dev->parent);
	struct fw_unit *unit = fw_unit(dev);

	return snprintf(buf, PAGE_SIZE, "%d\n",
			(int)(unit->directory - device->config_rom));
}