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
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int RTL8366RB_NUM_PORTS ; 
 int RTL8366RB_NUM_VLANS ; 
 int RTL8366RB_PORT_VLAN_CTRL_MASK ; 
 int /*<<< orphan*/  RTL8366RB_PORT_VLAN_CTRL_REG (int) ; 
 int RTL8366RB_PORT_VLAN_CTRL_SHIFT (int) ; 
 int rtl8366_smi_rmwr (struct rtl8366_smi*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int rtl8366rb_set_mc_index(struct rtl8366_smi *smi, int port, int index)
{
	if (port >= RTL8366RB_NUM_PORTS || index >= RTL8366RB_NUM_VLANS)
		return -EINVAL;

	return rtl8366_smi_rmwr(smi, RTL8366RB_PORT_VLAN_CTRL_REG(port),
				RTL8366RB_PORT_VLAN_CTRL_MASK <<
					RTL8366RB_PORT_VLAN_CTRL_SHIFT(port),
				(index & RTL8366RB_PORT_VLAN_CTRL_MASK) <<
					RTL8366RB_PORT_VLAN_CTRL_SHIFT(port));
}