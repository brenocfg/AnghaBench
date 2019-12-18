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
 int /*<<< orphan*/  F_BUSY ; 
 int /*<<< orphan*/  MDIO_ATTEMPTS ; 
 int /*<<< orphan*/  MDIO_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDIO_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_ST ; 
 unsigned int V_MDI_OP (int) ; 
 unsigned int V_PHYADDR (int) ; 
 unsigned int V_REGADDR (int) ; 
 int /*<<< orphan*/  V_ST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_set_reg_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t3_wait_op_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mi1_ext_write(adapter_t *adapter, int phy_addr, int mmd_addr,
			 int reg_addr, unsigned int val)
{
	int ret;
	u32 addr = V_REGADDR(mmd_addr) | V_PHYADDR(phy_addr);

	MDIO_LOCK(adapter);
	t3_set_reg_field(adapter, A_MI1_CFG, V_ST(M_ST), 0);
	t3_write_reg(adapter, A_MI1_ADDR, addr);
	t3_write_reg(adapter, A_MI1_DATA, reg_addr);
	t3_write_reg(adapter, A_MI1_OP, V_MDI_OP(0));
	ret = t3_wait_op_done(adapter, A_MI1_OP, F_BUSY, 0, MDIO_ATTEMPTS, 10);
	if (!ret) {
		t3_write_reg(adapter, A_MI1_DATA, val);
		t3_write_reg(adapter, A_MI1_OP, V_MDI_OP(1));
		ret = t3_wait_op_done(adapter, A_MI1_OP, F_BUSY, 0,
				      MDIO_ATTEMPTS, 10);
	}
	MDIO_UNLOCK(adapter);
	return ret;
}