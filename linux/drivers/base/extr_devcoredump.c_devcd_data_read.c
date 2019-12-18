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
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct device {int dummy; } ;
struct devcd_entry {int /*<<< orphan*/  datalen; int /*<<< orphan*/  data; int /*<<< orphan*/  (* read ) (char*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct bin_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 struct devcd_entry* dev_to_devcd (struct device*) ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t devcd_data_read(struct file *filp, struct kobject *kobj,
			       struct bin_attribute *bin_attr,
			       char *buffer, loff_t offset, size_t count)
{
	struct device *dev = kobj_to_dev(kobj);
	struct devcd_entry *devcd = dev_to_devcd(dev);

	return devcd->read(buffer, offset, count, devcd->data, devcd->datalen);
}