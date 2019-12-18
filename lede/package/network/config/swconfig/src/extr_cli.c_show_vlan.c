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
struct switch_val {int port_vlan; int /*<<< orphan*/  len; } ;
struct switch_dev {int /*<<< orphan*/  vlan_ops; } ;
struct switch_attr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWLIB_ATTR_GROUP_VLAN ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  show_attrs (struct switch_dev*,int /*<<< orphan*/ ,struct switch_val*) ; 
 scalar_t__ swlib_get_attr (struct switch_dev*,struct switch_attr*,struct switch_val*) ; 
 struct switch_attr* swlib_lookup_attr (struct switch_dev*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
show_vlan(struct switch_dev *dev, int vlan, bool all)
{
	struct switch_val val;
	struct switch_attr *attr;

	val.port_vlan = vlan;

	if (all) {
		attr = swlib_lookup_attr(dev, SWLIB_ATTR_GROUP_VLAN, "ports");
		if (swlib_get_attr(dev, attr, &val) < 0)
			return;

		if (!val.len)
			return;
	}

	printf("VLAN %d:\n", vlan);
	show_attrs(dev, dev->vlan_ops, &val);
}