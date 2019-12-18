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
struct omap_sham_dev {long fallback_sz; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct omap_sham_dev* dev_get_drvdata (struct device*) ; 
 size_t kstrtol (char const*,int /*<<< orphan*/ ,long*) ; 

__attribute__((used)) static ssize_t fallback_store(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t size)
{
	struct omap_sham_dev *dd = dev_get_drvdata(dev);
	ssize_t status;
	long value;

	status = kstrtol(buf, 0, &value);
	if (status)
		return status;

	/* HW accelerator only works with buffers > 9 */
	if (value < 9) {
		dev_err(dev, "minimum fallback size 9\n");
		return -EINVAL;
	}

	dd->fallback_sz = value;

	return size;
}