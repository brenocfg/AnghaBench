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
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (char const*,size_t,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 struct amba_device* to_amba_device (struct device*) ; 

__attribute__((used)) static ssize_t driver_override_store(struct device *_dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct amba_device *dev = to_amba_device(_dev);
	char *driver_override, *old, *cp;

	/* We need to keep extra room for a newline */
	if (count >= (PAGE_SIZE - 1))
		return -EINVAL;

	driver_override = kstrndup(buf, count, GFP_KERNEL);
	if (!driver_override)
		return -ENOMEM;

	cp = strchr(driver_override, '\n');
	if (cp)
		*cp = '\0';

	device_lock(_dev);
	old = dev->driver_override;
	if (strlen(driver_override)) {
		dev->driver_override = driver_override;
	} else {
		kfree(driver_override);
		dev->driver_override = NULL;
	}
	device_unlock(_dev);

	kfree(old);

	return count;
}