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
struct switch_dev {struct switch_attr* vlan_ops; struct switch_attr* port_ops; struct switch_attr* ops; } ;
struct switch_attr {struct switch_attr* next; int /*<<< orphan*/  name; } ;
typedef  enum swlib_attr_group { ____Placeholder_swlib_attr_group } swlib_attr_group ;

/* Variables and functions */
#define  SWLIB_ATTR_GROUP_GLOBAL 130 
#define  SWLIB_ATTR_GROUP_PORT 129 
#define  SWLIB_ATTR_GROUP_VLAN 128 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

struct switch_attr *swlib_lookup_attr(struct switch_dev *dev,
		enum swlib_attr_group atype, const char *name)
{
	struct switch_attr *head;

	if (!name || !dev)
		return NULL;

	switch(atype) {
	case SWLIB_ATTR_GROUP_GLOBAL:
		head = dev->ops;
		break;
	case SWLIB_ATTR_GROUP_PORT:
		head = dev->port_ops;
		break;
	case SWLIB_ATTR_GROUP_VLAN:
		head = dev->vlan_ops;
		break;
	}
	while(head) {
		if (!strcmp(name, head->name))
			return head;
		head = head->next;
	}

	return NULL;
}