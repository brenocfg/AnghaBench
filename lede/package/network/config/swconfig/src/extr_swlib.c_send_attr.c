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
struct switch_val {int /*<<< orphan*/  port_vlan; struct switch_attr* attr; } ;
struct switch_attr {int atype; int /*<<< orphan*/  id; TYPE_1__* dev; } ;
struct nl_msg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT_U32 (struct nl_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_ATTR_ID ; 
 int /*<<< orphan*/  SWITCH_ATTR_OP_ID ; 
 int /*<<< orphan*/  SWITCH_ATTR_OP_PORT ; 
 int /*<<< orphan*/  SWITCH_ATTR_OP_VLAN ; 
#define  SWLIB_ATTR_GROUP_PORT 129 
#define  SWLIB_ATTR_GROUP_VLAN 128 

__attribute__((used)) static int
send_attr(struct nl_msg *msg, void *arg)
{
	struct switch_val *val = arg;
	struct switch_attr *attr = val->attr;

	NLA_PUT_U32(msg, SWITCH_ATTR_ID, attr->dev->id);
	NLA_PUT_U32(msg, SWITCH_ATTR_OP_ID, attr->id);
	switch(attr->atype) {
	case SWLIB_ATTR_GROUP_PORT:
		NLA_PUT_U32(msg, SWITCH_ATTR_OP_PORT, val->port_vlan);
		break;
	case SWLIB_ATTR_GROUP_VLAN:
		NLA_PUT_U32(msg, SWITCH_ATTR_OP_VLAN, val->port_vlan);
		break;
	default:
		break;
	}

	return 0;

nla_put_failure:
	return -1;
}