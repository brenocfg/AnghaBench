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
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct vpd_attrib_info {TYPE_1__ bin_attr; int /*<<< orphan*/  value; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {struct vpd_attrib_info* private; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  memory_read_from_buffer (char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t vpd_attrib_read(struct file *filp, struct kobject *kobp,
			       struct bin_attribute *bin_attr, char *buf,
			       loff_t pos, size_t count)
{
	struct vpd_attrib_info *info = bin_attr->private;

	return memory_read_from_buffer(buf, count, &pos, info->value,
				       info->bin_attr.size);
}