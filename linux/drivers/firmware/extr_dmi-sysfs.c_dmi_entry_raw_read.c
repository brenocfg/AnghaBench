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
struct dmi_sysfs_entry {int dummy; } ;
struct dmi_read_state {char* buf; size_t count; int /*<<< orphan*/  pos; } ;
struct bin_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmi_entry_raw_read_helper ; 
 int /*<<< orphan*/  find_dmi_entry (struct dmi_sysfs_entry*,int /*<<< orphan*/ ,struct dmi_read_state*) ; 
 struct dmi_sysfs_entry* to_entry (struct kobject*) ; 

__attribute__((used)) static ssize_t dmi_entry_raw_read(struct file *filp,
				  struct kobject *kobj,
				  struct bin_attribute *bin_attr,
				  char *buf, loff_t pos, size_t count)
{
	struct dmi_sysfs_entry *entry = to_entry(kobj);
	struct dmi_read_state state = {
		.buf = buf,
		.pos = pos,
		.count = count,
	};

	return find_dmi_entry(entry, dmi_entry_raw_read_helper, &state);
}