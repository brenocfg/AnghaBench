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
struct dmi_sysfs_entry {int dummy; } ;
struct dmi_sysfs_attribute {int /*<<< orphan*/  (* show ) (struct dmi_sysfs_entry*,char*) ;} ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dmi_sysfs_entry*,char*) ; 
 struct dmi_sysfs_attribute* to_attr (struct attribute*) ; 
 struct dmi_sysfs_entry* to_entry (struct kobject*) ; 

__attribute__((used)) static ssize_t dmi_sysfs_attr_show(struct kobject *kobj,
				   struct attribute *_attr, char *buf)
{
	struct dmi_sysfs_entry *entry = to_entry(kobj);
	struct dmi_sysfs_attribute *attr = to_attr(_attr);

	/* DMI stuff is only ever admin visible */
	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	return attr->show(entry, buf);
}