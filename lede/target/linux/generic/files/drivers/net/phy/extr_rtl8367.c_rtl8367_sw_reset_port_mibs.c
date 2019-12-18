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
struct switch_val {int port_vlan; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RTL8367_MIB_CTRL_PORT_RESET_MASK (int) ; 
 int /*<<< orphan*/  RTL8367_MIB_CTRL_REG (int) ; 
 int RTL8367_NUM_PORTS ; 
 int rtl8366_smi_rmwr (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl8366_smi* sw_to_rtl8366_smi (struct switch_dev*) ; 

__attribute__((used)) static int rtl8367_sw_reset_port_mibs(struct switch_dev *dev,
				       const struct switch_attr *attr,
				       struct switch_val *val)
{
	struct rtl8366_smi *smi = sw_to_rtl8366_smi(dev);
	int port;

	port = val->port_vlan;
	if (port >= RTL8367_NUM_PORTS)
		return -EINVAL;

	return rtl8366_smi_rmwr(smi, RTL8367_MIB_CTRL_REG(port / 8), 0,
				RTL8367_MIB_CTRL_PORT_RESET_MASK(port % 8));
}