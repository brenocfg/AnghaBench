#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct mem_ctl_info {struct i7core_pvt* pvt_info; } ;
struct TYPE_2__ {scalar_t__ section; scalar_t__ enable; } ;
struct i7core_pvt {TYPE_1__ inject; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EIO ; 
 int /*<<< orphan*/  disable_inject (struct mem_ctl_info*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 struct mem_ctl_info* to_mci (struct device*) ; 

__attribute__((used)) static ssize_t i7core_inject_section_store(struct device *dev,
					   struct device_attribute *mattr,
					   const char *data, size_t count)
{
	struct mem_ctl_info *mci = to_mci(dev);
	struct i7core_pvt *pvt = mci->pvt_info;
	unsigned long value;
	int rc;

	if (pvt->inject.enable)
		disable_inject(mci);

	rc = kstrtoul(data, 10, &value);
	if ((rc < 0) || (value > 3))
		return -EIO;

	pvt->inject.section = (u32) value;
	return count;
}