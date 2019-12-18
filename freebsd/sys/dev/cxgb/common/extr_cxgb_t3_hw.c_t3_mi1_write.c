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
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_MI1_ADDR ; 
 int /*<<< orphan*/  A_MI1_CFG ; 
 int /*<<< orphan*/  A_MI1_DATA ; 
 int /*<<< orphan*/  A_MI1_OP ; 
 int EINVAL ; 
 int /*<<< orphan*/  F_BUSY ; 
 int /*<<< orphan*/  MDIO_ATTEMPTS ; 
 int /*<<< orphan*/  MDIO_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDIO_UNLOCK (int /*<<< orphan*/ *) ; 
 int M_ST ; 
 unsigned int V_MDI_OP (int) ; 
 unsigned int V_PHYADDR (int) ; 
 unsigned int V_REGADDR (int) ; 
 int /*<<< orphan*/  V_ST (int) ; 
 int /*<<< orphan*/  t3_set_reg_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t3_wait_op_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

int t3_mi1_write(adapter_t *adapter, int phy_addr, int mmd_addr,
		 int reg_addr, unsigned int val)
{
	int ret;
	u32 addr = V_REGADDR(reg_addr) | V_PHYADDR(phy_addr);

	if (mmd_addr)
		return -EINVAL;

	MDIO_LOCK(adapter);
	t3_set_reg_field(adapter, A_MI1_CFG, V_ST(M_ST), V_ST(1));
	t3_write_reg(adapter, A_MI1_ADDR, addr);
	t3_write_reg(adapter, A_MI1_DATA, val);
	t3_write_reg(adapter, A_MI1_OP, V_MDI_OP(1));
	ret = t3_wait_op_done(adapter, A_MI1_OP, F_BUSY, 0, MDIO_ATTEMPTS, 10);
	MDIO_UNLOCK(adapter);
	return ret;
}