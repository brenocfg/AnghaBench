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
struct gendisk {struct aoedev* private_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct aoetgt {int /*<<< orphan*/  addr; } ;
struct aoedev {struct aoetgt** targets; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct gendisk* dev_to_disk (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ssize_t aoedisk_show_mac(struct device *dev,
				struct device_attribute *attr, char *page)
{
	struct gendisk *disk = dev_to_disk(dev);
	struct aoedev *d = disk->private_data;
	struct aoetgt *t = d->targets[0];

	if (t == NULL)
		return snprintf(page, PAGE_SIZE, "none\n");
	return snprintf(page, PAGE_SIZE, "%pm\n", t->addr);
}