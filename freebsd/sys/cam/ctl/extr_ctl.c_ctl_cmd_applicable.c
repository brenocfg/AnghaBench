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
typedef  int uint8_t ;
struct ctl_cmd_entry {int flags; } ;

/* Variables and functions */
 int CTL_CMD_FLAG_OK_ON_CDROM ; 
 int CTL_CMD_FLAG_OK_ON_DIRECT ; 
 int CTL_CMD_FLAG_OK_ON_PROC ; 
#define  T_CDROM 130 
#define  T_DIRECT 129 
#define  T_PROCESSOR 128 

__attribute__((used)) static int
ctl_cmd_applicable(uint8_t lun_type, const struct ctl_cmd_entry *entry)
{

	switch (lun_type) {
	case T_DIRECT:
		if ((entry->flags & CTL_CMD_FLAG_OK_ON_DIRECT) == 0)
			return (0);
		break;
	case T_PROCESSOR:
		if ((entry->flags & CTL_CMD_FLAG_OK_ON_PROC) == 0)
			return (0);
		break;
	case T_CDROM:
		if ((entry->flags & CTL_CMD_FLAG_OK_ON_CDROM) == 0)
			return (0);
		break;
	default:
		return (0);
	}
	return (1);
}