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
struct dmi_system_event_log {int access_method; } ;
struct dmi_sysfs_entry {int dummy; } ;
struct dmi_read_state {int /*<<< orphan*/  count; int /*<<< orphan*/  pos; int /*<<< orphan*/  buf; } ;
struct dmi_header {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  sel ;

/* Variables and functions */
#define  DMI_SEL_ACCESS_METHOD_GPNV 132 
#define  DMI_SEL_ACCESS_METHOD_IO16 131 
#define  DMI_SEL_ACCESS_METHOD_IO2x8 130 
#define  DMI_SEL_ACCESS_METHOD_IO8 129 
#define  DMI_SEL_ACCESS_METHOD_PHYS32 128 
 int /*<<< orphan*/  EIO ; 
 int dmi_entry_length (struct dmi_header const*) ; 
 int /*<<< orphan*/  dmi_sel_raw_read_io (struct dmi_sysfs_entry*,struct dmi_system_event_log*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmi_sel_raw_read_phys32 (struct dmi_sysfs_entry*,struct dmi_system_event_log*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct dmi_system_event_log*,struct dmi_header const*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static ssize_t dmi_sel_raw_read_helper(struct dmi_sysfs_entry *entry,
				       const struct dmi_header *dh,
				       void *_state)
{
	struct dmi_read_state *state = _state;
	struct dmi_system_event_log sel;

	if (sizeof(sel) > dmi_entry_length(dh))
		return -EIO;

	memcpy(&sel, dh, sizeof(sel));

	switch (sel.access_method) {
	case DMI_SEL_ACCESS_METHOD_IO8:
	case DMI_SEL_ACCESS_METHOD_IO2x8:
	case DMI_SEL_ACCESS_METHOD_IO16:
		return dmi_sel_raw_read_io(entry, &sel, state->buf,
					   state->pos, state->count);
	case DMI_SEL_ACCESS_METHOD_PHYS32:
		return dmi_sel_raw_read_phys32(entry, &sel, state->buf,
					       state->pos, state->count);
	case DMI_SEL_ACCESS_METHOD_GPNV:
		pr_info("dmi-sysfs: GPNV support missing.\n");
		return -EIO;
	default:
		pr_info("dmi-sysfs: Unknown access method %02x\n",
			sel.access_method);
		return -EIO;
	}
}