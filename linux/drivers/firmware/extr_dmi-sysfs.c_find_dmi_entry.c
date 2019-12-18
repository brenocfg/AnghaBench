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
struct find_dmi_data {void* private; int /*<<< orphan*/  ret; int /*<<< orphan*/  instance_countdown; int /*<<< orphan*/  callback; struct dmi_sysfs_entry* entry; } ;
struct dmi_sysfs_entry {int /*<<< orphan*/  instance; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  dmi_callback ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int dmi_walk (int /*<<< orphan*/ ,struct find_dmi_data*) ; 
 int /*<<< orphan*/  find_dmi_entry_helper ; 

__attribute__((used)) static ssize_t find_dmi_entry(struct dmi_sysfs_entry *entry,
			      dmi_callback callback, void *private)
{
	struct find_dmi_data data = {
		.entry = entry,
		.callback = callback,
		.private = private,
		.instance_countdown = entry->instance,
		.ret = -EIO,  /* To signal the entry disappeared */
	};
	int ret;

	ret = dmi_walk(find_dmi_entry_helper, &data);
	/* This shouldn't happen, but just in case. */
	if (ret)
		return -EINVAL;
	return data.ret;
}