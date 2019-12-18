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
struct ctl_scsiio {size_t* cdb; } ;
struct ctl_cmd_entry {int flags; scalar_t__ execute; } ;

/* Variables and functions */
 int CTL_CMD_FLAG_SA5 ; 
 int SERVICE_ACTION_MASK ; 
 struct ctl_cmd_entry* ctl_cmd_table ; 

const struct ctl_cmd_entry *
ctl_get_cmd_entry(struct ctl_scsiio *ctsio, int *sa)
{
	const struct ctl_cmd_entry *entry;
	int service_action;

	entry = &ctl_cmd_table[ctsio->cdb[0]];
	if (sa)
		*sa = ((entry->flags & CTL_CMD_FLAG_SA5) != 0);
	if (entry->flags & CTL_CMD_FLAG_SA5) {
		service_action = ctsio->cdb[1] & SERVICE_ACTION_MASK;
		entry = &((const struct ctl_cmd_entry *)
		    entry->execute)[service_action];
	}
	return (entry);
}