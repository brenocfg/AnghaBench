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
struct switch_val {struct switch_attr* attr; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int atype; } ;

/* Variables and functions */
 int EINVAL ; 
 int SWITCH_CMD_SET_GLOBAL ; 
 int SWITCH_CMD_SET_PORT ; 
 int SWITCH_CMD_SET_VLAN ; 
#define  SWLIB_ATTR_GROUP_GLOBAL 130 
#define  SWLIB_ATTR_GROUP_PORT 129 
#define  SWLIB_ATTR_GROUP_VLAN 128 
 int /*<<< orphan*/  send_attr_val ; 
 int swlib_call (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct switch_val*) ; 

int
swlib_set_attr(struct switch_dev *dev, struct switch_attr *attr, struct switch_val *val)
{
	int cmd;

	switch(attr->atype) {
	case SWLIB_ATTR_GROUP_GLOBAL:
		cmd = SWITCH_CMD_SET_GLOBAL;
		break;
	case SWLIB_ATTR_GROUP_PORT:
		cmd = SWITCH_CMD_SET_PORT;
		break;
	case SWLIB_ATTR_GROUP_VLAN:
		cmd = SWITCH_CMD_SET_VLAN;
		break;
	default:
		return -EINVAL;
	}

	val->attr = attr;
	return swlib_call(cmd, NULL, send_attr_val, val);
}