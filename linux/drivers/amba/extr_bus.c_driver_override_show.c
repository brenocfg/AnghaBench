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
struct amba_device {char* driver_override; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct amba_device* to_amba_device (struct device*) ; 

__attribute__((used)) static ssize_t driver_override_show(struct device *_dev,
				    struct device_attribute *attr, char *buf)
{
	struct amba_device *dev = to_amba_device(_dev);
	ssize_t len;

	device_lock(_dev);
	len = sprintf(buf, "%s\n", dev->driver_override);
	device_unlock(_dev);
	return len;
}