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
struct ps3_system_bus_device {int match_id; int match_sub_id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 struct ps3_system_bus_device* ps3_dev_to_system_bus_dev (struct device*) ; 
 int snprintf (char*,int,char*,int,int) ; 

__attribute__((used)) static ssize_t modalias_show(struct device *_dev, struct device_attribute *a,
	char *buf)
{
	struct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);
	int len = snprintf(buf, PAGE_SIZE, "ps3:%d:%d\n", dev->match_id,
			   dev->match_sub_id);

	return (len >= PAGE_SIZE) ? (PAGE_SIZE - 1) : len;
}