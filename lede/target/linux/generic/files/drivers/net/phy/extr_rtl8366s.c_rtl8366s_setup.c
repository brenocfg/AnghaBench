#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rtl8366_smi {TYPE_2__* parent; } ;
struct rtl8366_platform_data {unsigned int num_initvals; TYPE_1__* initvals; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {struct device_node* of_node; struct rtl8366_platform_data* platform_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_RMW (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int RTL8366S_PHY_NO_MAX ; 
 int /*<<< orphan*/  RTL8366S_PORT_ALL ; 
 int /*<<< orphan*/  RTL8366S_SGCR ; 
 int /*<<< orphan*/  RTL8366S_SGCR_MAX_LENGTH_1536 ; 
 int /*<<< orphan*/  RTL8366S_SGCR_MAX_LENGTH_MASK ; 
 int /*<<< orphan*/  RTL8366S_SSCR0 ; 
 int /*<<< orphan*/  RTL8366S_SSCR1 ; 
 int /*<<< orphan*/  RTL8366S_SSCR2 ; 
 int /*<<< orphan*/  RTL8366S_SSCR2_DROP_UNKNOWN_DA ; 
 int /*<<< orphan*/  RTL8366S_VLAN_MEMBERINGRESS_REG ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,unsigned int*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int rtl8366s_set_green (struct rtl8366_smi*,int) ; 
 int rtl8366s_set_green_port (struct rtl8366_smi*,unsigned int,int) ; 

__attribute__((used)) static int rtl8366s_setup(struct rtl8366_smi *smi)
{
	struct rtl8366_platform_data *pdata;
	int err;
	unsigned i;
#ifdef CONFIG_OF
	struct device_node *np;
	unsigned num_initvals;
	const __be32 *paddr;
#endif

	pdata = smi->parent->platform_data;
	if (pdata && pdata->num_initvals && pdata->initvals) {
		dev_info(smi->parent, "applying initvals\n");
		for (i = 0; i < pdata->num_initvals; i++)
			REG_WR(smi, pdata->initvals[i].reg,
			       pdata->initvals[i].val);
	}

#ifdef CONFIG_OF
	np = smi->parent->of_node;

	paddr = of_get_property(np, "realtek,initvals", &num_initvals);
	if (paddr) {
		dev_info(smi->parent, "applying initvals from DTS\n");

		if (num_initvals < (2 * sizeof(*paddr)))
			return -EINVAL;

		num_initvals /= sizeof(*paddr);

		for (i = 0; i < num_initvals - 1; i += 2) {
			u32 reg = be32_to_cpup(paddr + i);
			u32 val = be32_to_cpup(paddr + i + 1);

			REG_WR(smi, reg, val);
		}
	}

	if (of_property_read_bool(np, "realtek,green-ethernet-features")) {
		dev_info(smi->parent, "activating Green Ethernet features\n");

		err = rtl8366s_set_green(smi, 1);
		if (err)
			return err;

		for (i = 0; i <= RTL8366S_PHY_NO_MAX; i++) {
			err = rtl8366s_set_green_port(smi, i, 1);
			if (err)
				return err;
		}
	}
#endif

	/* set maximum packet length to 1536 bytes */
	REG_RMW(smi, RTL8366S_SGCR, RTL8366S_SGCR_MAX_LENGTH_MASK,
		RTL8366S_SGCR_MAX_LENGTH_1536);

	/* enable learning for all ports */
	REG_WR(smi, RTL8366S_SSCR0, 0);

	/* enable auto ageing for all ports */
	REG_WR(smi, RTL8366S_SSCR1, 0);

	/*
	 * discard VLAN tagged packets if the port is not a member of
	 * the VLAN with which the packets is associated.
	 */
	REG_WR(smi, RTL8366S_VLAN_MEMBERINGRESS_REG, RTL8366S_PORT_ALL);

	/* don't drop packets whose DA has not been learned */
	REG_RMW(smi, RTL8366S_SSCR2, RTL8366S_SSCR2_DROP_UNKNOWN_DA, 0);

	return 0;
}