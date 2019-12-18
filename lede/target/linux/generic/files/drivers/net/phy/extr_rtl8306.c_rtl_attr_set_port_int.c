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
struct switch_val {scalar_t__ port_vlan; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RTL8306_NUM_PORTS ; 
 int rtl_attr_set_int (struct switch_dev*,struct switch_attr const*,struct switch_val*) ; 

__attribute__((used)) static int
rtl_attr_set_port_int(struct switch_dev *dev, const struct switch_attr *attr, struct switch_val *val)
{
	if (val->port_vlan >= RTL8306_NUM_PORTS)
		return -EINVAL;

	return rtl_attr_set_int(dev, attr, val);
}