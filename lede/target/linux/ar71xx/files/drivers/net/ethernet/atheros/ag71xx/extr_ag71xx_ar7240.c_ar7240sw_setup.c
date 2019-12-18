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
struct mii_bus {int dummy; } ;
struct ar7240sw {struct mii_bus* mii_bus; } ;

/* Variables and functions */
 int AR7240_AT_CTRL_AGE_EN ; 
 int AR7240_AT_CTRL_ARP_EN ; 
 int AR7240_AT_CTRL_LEARN_CHANGE ; 
 int AR7240_AT_CTRL_RESERVED ; 
 int AR7240_CPU_PORT_EN ; 
 int AR7240_FLOOD_MASK_BROAD_TO_CPU ; 
 int /*<<< orphan*/  AR7240_GLOBAL_CTRL_MTU_M ; 
 int AR7240_MIRROR_PORT_S ; 
 int /*<<< orphan*/  AR7240_REG_AT_CTRL ; 
 int /*<<< orphan*/  AR7240_REG_CPU_PORT ; 
 int /*<<< orphan*/  AR7240_REG_FLOOD_MASK ; 
 int /*<<< orphan*/  AR7240_REG_GLOBAL_CTRL ; 
 int /*<<< orphan*/  AR7240_REG_MIB_FUNCTION0 ; 
 int /*<<< orphan*/  AR7240_REG_SERVICE_TAG ; 
 int /*<<< orphan*/  AR7240_REG_TAG_PRIORITY ; 
 int /*<<< orphan*/  AR7240_SERVICE_TAG_M ; 
 int /*<<< orphan*/  AR9340_GLOBAL_CTRL_MTU_M ; 
 int AR934X_AT_CTRL_AGE_EN ; 
 int AR934X_AT_CTRL_LEARN_CHANGE ; 
 int AR934X_FLOOD_MASK_BC_DP (int /*<<< orphan*/ ) ; 
 int AR934X_FLOOD_MASK_MC_DP (int /*<<< orphan*/ ) ; 
 int AR934X_MIB_ENABLE ; 
 int AR934X_QM_CTRL_ARP_EN ; 
 int /*<<< orphan*/  AR934X_REG_AT_CTRL ; 
 int /*<<< orphan*/  AR934X_REG_FLOOD_MASK ; 
 int /*<<< orphan*/  AR934X_REG_QM_CTRL ; 
 int /*<<< orphan*/  ar7240sw_reg_rmw (struct mii_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar7240sw_reg_set (struct mii_bus*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar7240sw_reg_write (struct mii_bus*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sw_is_ar934x (struct ar7240sw*) ; 

__attribute__((used)) static void ar7240sw_setup(struct ar7240sw *as)
{
	struct mii_bus *mii = as->mii_bus;

	/* Enable CPU port, and disable mirror port */
	ar7240sw_reg_write(mii, AR7240_REG_CPU_PORT,
			   AR7240_CPU_PORT_EN |
			   (15 << AR7240_MIRROR_PORT_S));

	/* Setup TAG priority mapping */
	ar7240sw_reg_write(mii, AR7240_REG_TAG_PRIORITY, 0xfa50);

	if (sw_is_ar934x(as)) {
		/* Enable aging, MAC replacing */
		ar7240sw_reg_write(mii, AR934X_REG_AT_CTRL,
			0x2b /* 5 min age time */ |
			AR934X_AT_CTRL_AGE_EN |
			AR934X_AT_CTRL_LEARN_CHANGE);
		/* Enable ARP frame acknowledge */
		ar7240sw_reg_set(mii, AR934X_REG_QM_CTRL,
				 AR934X_QM_CTRL_ARP_EN);
		/* Enable Broadcast/Multicast frames transmitted to the CPU */
		ar7240sw_reg_set(mii, AR934X_REG_FLOOD_MASK,
				 AR934X_FLOOD_MASK_BC_DP(0) |
				 AR934X_FLOOD_MASK_MC_DP(0));

		/* setup MTU */
		ar7240sw_reg_rmw(mii, AR7240_REG_GLOBAL_CTRL,
				 AR9340_GLOBAL_CTRL_MTU_M,
				 AR9340_GLOBAL_CTRL_MTU_M);

		/* Enable MIB counters */
		ar7240sw_reg_set(mii, AR7240_REG_MIB_FUNCTION0,
				 AR934X_MIB_ENABLE);

	} else {
		/* Enable ARP frame acknowledge, aging, MAC replacing */
		ar7240sw_reg_write(mii, AR7240_REG_AT_CTRL,
			AR7240_AT_CTRL_RESERVED |
			0x2b /* 5 min age time */ |
			AR7240_AT_CTRL_AGE_EN |
			AR7240_AT_CTRL_ARP_EN |
			AR7240_AT_CTRL_LEARN_CHANGE);
		/* Enable Broadcast frames transmitted to the CPU */
		ar7240sw_reg_set(mii, AR7240_REG_FLOOD_MASK,
				 AR7240_FLOOD_MASK_BROAD_TO_CPU);

		/* setup MTU */
		ar7240sw_reg_rmw(mii, AR7240_REG_GLOBAL_CTRL,
				 AR7240_GLOBAL_CTRL_MTU_M,
				 AR7240_GLOBAL_CTRL_MTU_M);
	}

	/* setup Service TAG */
	ar7240sw_reg_rmw(mii, AR7240_REG_SERVICE_TAG, AR7240_SERVICE_TAG_M, 0);
}