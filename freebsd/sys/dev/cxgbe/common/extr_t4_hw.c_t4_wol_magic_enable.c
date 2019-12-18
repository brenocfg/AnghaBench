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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_MAC_PORT_CFG2 ; 
 int /*<<< orphan*/  A_MAC_PORT_MAGIC_MACID_HI ; 
 int /*<<< orphan*/  A_MAC_PORT_MAGIC_MACID_LO ; 
 int /*<<< orphan*/  A_XGMAC_PORT_CFG2 ; 
 int /*<<< orphan*/  A_XGMAC_PORT_MAGIC_MACID_HI ; 
 int /*<<< orphan*/  A_XGMAC_PORT_MAGIC_MACID_LO ; 
 int /*<<< orphan*/  F_MAGICEN ; 
 int /*<<< orphan*/  PORT_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T5_PORT_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_MAGICEN (int /*<<< orphan*/ ) ; 
 scalar_t__ is_t4 (struct adapter*) ; 
 int /*<<< orphan*/  t4_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int const) ; 

void t4_wol_magic_enable(struct adapter *adap, unsigned int port,
			 const u8 *addr)
{
	u32 mag_id_reg_l, mag_id_reg_h, port_cfg_reg;

	if (is_t4(adap)) {
		mag_id_reg_l = PORT_REG(port, A_XGMAC_PORT_MAGIC_MACID_LO);
		mag_id_reg_h = PORT_REG(port, A_XGMAC_PORT_MAGIC_MACID_HI);
		port_cfg_reg = PORT_REG(port, A_XGMAC_PORT_CFG2);
	} else {
		mag_id_reg_l = T5_PORT_REG(port, A_MAC_PORT_MAGIC_MACID_LO);
		mag_id_reg_h = T5_PORT_REG(port, A_MAC_PORT_MAGIC_MACID_HI);
		port_cfg_reg = T5_PORT_REG(port, A_MAC_PORT_CFG2);
	}

	if (addr) {
		t4_write_reg(adap, mag_id_reg_l,
			     (addr[2] << 24) | (addr[3] << 16) |
			     (addr[4] << 8) | addr[5]);
		t4_write_reg(adap, mag_id_reg_h,
			     (addr[0] << 8) | addr[1]);
	}
	t4_set_reg_field(adap, port_cfg_reg, F_MAGICEN,
			 V_MAGICEN(addr != NULL));
}