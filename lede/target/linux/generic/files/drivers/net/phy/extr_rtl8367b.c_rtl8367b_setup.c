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
struct rtl8367_platform_data {int /*<<< orphan*/  extif1_cfg; int /*<<< orphan*/  extif0_cfg; } ;
struct rtl8366_smi {TYPE_1__* parent; } ;
struct TYPE_2__ {scalar_t__ of_node; struct rtl8367_platform_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_RMW (struct rtl8366_smi*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_WR (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RTL8367B_NUM_PORTS ; 
 int /*<<< orphan*/  RTL8367B_PORTS_ALL ; 
 int RTL8367B_PORT_MISC_CFG_EGRESS_MODE_MASK ; 
 int RTL8367B_PORT_MISC_CFG_EGRESS_MODE_ORIGINAL ; 
 int RTL8367B_PORT_MISC_CFG_EGRESS_MODE_SHIFT ; 
 int /*<<< orphan*/  RTL8367B_PORT_MISC_CFG_REG (int) ; 
 int RTL8367B_SWC0_MAX_LENGTH_1536 ; 
 int RTL8367B_SWC0_MAX_LENGTH_MASK ; 
 int /*<<< orphan*/  RTL8367B_SWC0_REG ; 
 int /*<<< orphan*/  RTL8367B_VLAN_INGRESS_REG ; 
 int rtl8367b_extif_init (struct rtl8366_smi*,int,int /*<<< orphan*/ ) ; 
 int rtl8367b_extif_init_of (struct rtl8366_smi*,int,char*) ; 
 int rtl8367b_init_regs (struct rtl8366_smi*) ; 

__attribute__((used)) static int rtl8367b_setup(struct rtl8366_smi *smi)
{
	struct rtl8367_platform_data *pdata;
	int err;
	int i;

	pdata = smi->parent->platform_data;

	err = rtl8367b_init_regs(smi);
	if (err)
		return err;

	/* initialize external interfaces */
	if (smi->parent->of_node) {
		err = rtl8367b_extif_init_of(smi, 0, "realtek,extif0");
		if (err)
			return err;

		err = rtl8367b_extif_init_of(smi, 1, "realtek,extif1");
		if (err)
			return err;
	} else {
		err = rtl8367b_extif_init(smi, 0, pdata->extif0_cfg);
		if (err)
			return err;

		err = rtl8367b_extif_init(smi, 1, pdata->extif1_cfg);
		if (err)
			return err;
	}

	/* set maximum packet length to 1536 bytes */
	REG_RMW(smi, RTL8367B_SWC0_REG, RTL8367B_SWC0_MAX_LENGTH_MASK,
		RTL8367B_SWC0_MAX_LENGTH_1536);

	/*
	 * discard VLAN tagged packets if the port is not a member of
	 * the VLAN with which the packets is associated.
	 */
	REG_WR(smi, RTL8367B_VLAN_INGRESS_REG, RTL8367B_PORTS_ALL);

	/*
	 * Setup egress tag mode for each port.
	 */
	for (i = 0; i < RTL8367B_NUM_PORTS; i++)
		REG_RMW(smi,
			RTL8367B_PORT_MISC_CFG_REG(i),
			RTL8367B_PORT_MISC_CFG_EGRESS_MODE_MASK <<
				RTL8367B_PORT_MISC_CFG_EGRESS_MODE_SHIFT,
			RTL8367B_PORT_MISC_CFG_EGRESS_MODE_ORIGINAL <<
				RTL8367B_PORT_MISC_CFG_EGRESS_MODE_SHIFT);

	return 0;
}