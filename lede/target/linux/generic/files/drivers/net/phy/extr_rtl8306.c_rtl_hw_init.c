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
struct switch_dev {int cpu_port; } ;
struct rtl_priv {scalar_t__ do_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_VID_REPLACE ; 
 int /*<<< orphan*/  PORTMASK ; 
 int /*<<< orphan*/  PVID ; 
 int RTL8306_NUM_PORTS ; 
 int RTL8306_NUM_VLANS ; 
 int /*<<< orphan*/  RTL_PORT_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_REG_CPUPORT ; 
 int /*<<< orphan*/  RTL_REG_EN_CPUPORT ; 
 int /*<<< orphan*/  RTL_REG_EN_TAG_CLR ; 
 int /*<<< orphan*/  RTL_REG_EN_TAG_IN ; 
 int /*<<< orphan*/  RTL_REG_EN_TAG_OUT ; 
 int /*<<< orphan*/  RTL_REG_EN_TRUNK ; 
 int /*<<< orphan*/  RTL_REG_TRUNK_PORTSEL ; 
 int /*<<< orphan*/  RTL_REG_VLAN_ENABLE ; 
 int /*<<< orphan*/  RTL_REG_VLAN_FILTER ; 
 int /*<<< orphan*/  RTL_VLAN_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_INSERT ; 
 int /*<<< orphan*/  VID ; 
 int /*<<< orphan*/  VID_INSERT ; 
 int /*<<< orphan*/  rtl_hw_apply (struct switch_dev*) ; 
 int /*<<< orphan*/  rtl_set (struct switch_dev*,int /*<<< orphan*/ ,int) ; 
 struct rtl_priv* to_rtl (struct switch_dev*) ; 

__attribute__((used)) static void
rtl_hw_init(struct switch_dev *dev)
{
	struct rtl_priv *priv = to_rtl(dev);
	int cpu_mask = 1 << dev->cpu_port;
	int i;

	rtl_set(dev, RTL_REG_VLAN_ENABLE, 0);
	rtl_set(dev, RTL_REG_VLAN_FILTER, 0);
	rtl_set(dev, RTL_REG_EN_TRUNK, 0);
	rtl_set(dev, RTL_REG_TRUNK_PORTSEL, 0);

	/* initialize cpu port settings */
	if (priv->do_cpu) {
		rtl_set(dev, RTL_REG_CPUPORT, dev->cpu_port);
		rtl_set(dev, RTL_REG_EN_CPUPORT, 1);
	} else {
		rtl_set(dev, RTL_REG_CPUPORT, 7);
		rtl_set(dev, RTL_REG_EN_CPUPORT, 0);
	}
	rtl_set(dev, RTL_REG_EN_TAG_OUT, 0);
	rtl_set(dev, RTL_REG_EN_TAG_IN, 0);
	rtl_set(dev, RTL_REG_EN_TAG_CLR, 0);

	/* reset all vlans */
	for (i = 0; i < RTL8306_NUM_VLANS; i++) {
		rtl_set(dev, RTL_VLAN_REG(i, VID), i);
		rtl_set(dev, RTL_VLAN_REG(i, PORTMASK), 0);
	}

	/* default to port isolation */
	for (i = 0; i < RTL8306_NUM_PORTS; i++) {
		unsigned long mask;

		if ((1 << i) == cpu_mask)
			mask = ((1 << RTL8306_NUM_PORTS) - 1) & ~cpu_mask; /* all bits set */
		else
			mask = cpu_mask | (1 << i);

		rtl_set(dev, RTL_VLAN_REG(i, PORTMASK), mask);
		rtl_set(dev, RTL_PORT_REG(i, PVID), i);
		rtl_set(dev, RTL_PORT_REG(i, NULL_VID_REPLACE), 1);
		rtl_set(dev, RTL_PORT_REG(i, VID_INSERT), 1);
		rtl_set(dev, RTL_PORT_REG(i, TAG_INSERT), 3);
	}
	rtl_hw_apply(dev);
}