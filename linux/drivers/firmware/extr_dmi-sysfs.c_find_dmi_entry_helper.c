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
struct find_dmi_data {scalar_t__ instance_countdown; int /*<<< orphan*/  private; int /*<<< orphan*/  (* callback ) (struct dmi_sysfs_entry*,struct dmi_header const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ret; struct dmi_sysfs_entry* entry; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct dmi_sysfs_entry {TYPE_1__ dh; } ;
struct dmi_header {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dmi_sysfs_entry*,struct dmi_header const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_dmi_entry_helper(const struct dmi_header *dh,
				  void *_data)
{
	struct find_dmi_data *data = _data;
	struct dmi_sysfs_entry *entry = data->entry;

	/* Is this the entry we want? */
	if (dh->type != entry->dh.type)
		return;

	if (data->instance_countdown != 0) {
		/* try the next instance? */
		data->instance_countdown--;
		return;
	}

	/*
	 * Don't ever revisit the instance.  Short circuit later
	 * instances by letting the instance_countdown run negative
	 */
	data->instance_countdown--;

	/* Found the entry */
	data->ret = data->callback(entry, dh, data->private);
}