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
typedef  int u32 ;

/* Variables and functions */
 unsigned char MAC_WT0_MAC0_SHIFT ; 
 unsigned char MAC_WT0_MAC1_SHIFT ; 
 unsigned char MAC_WT0_MAWC ; 
 int MAC_WT0_MWD ; 
 unsigned char MAC_WT0_WAF_SHIFT ; 
 unsigned char MAC_WT0_WAF_STATIC ; 
 unsigned char MAC_WT0_WVE ; 
 unsigned int MAC_WT0_WVN_SHIFT ; 
 unsigned char MAC_WT1_MAC3_SHIFT ; 
 unsigned char MAC_WT1_MAC4_SHIFT ; 
 unsigned char MAC_WT1_MAC5_SHIFT ; 
 int /*<<< orphan*/  SWITCH_REG_MAC_WT0 ; 
 int /*<<< orphan*/  SWITCH_REG_MAC_WT1 ; 
 int sw_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adm5120_switch_set_vlan_mac(unsigned int vlan, unsigned char *mac)
{
	u32 t;

	t = mac[2] | (mac[3] << MAC_WT1_MAC3_SHIFT)
		| (mac[4] << MAC_WT1_MAC4_SHIFT)
		| (mac[5] << MAC_WT1_MAC5_SHIFT);
	sw_write_reg(SWITCH_REG_MAC_WT1, t);

	t = (mac[0] << MAC_WT0_MAC0_SHIFT) | (mac[1] << MAC_WT0_MAC1_SHIFT) |
		MAC_WT0_MAWC | MAC_WT0_WVE | (vlan << MAC_WT0_WVN_SHIFT) |
		(MAC_WT0_WAF_STATIC << MAC_WT0_WAF_SHIFT);
	sw_write_reg(SWITCH_REG_MAC_WT0, t);

	do {
		t = sw_read_reg(SWITCH_REG_MAC_WT0);
	} while ((t & MAC_WT0_MWD) == 0);
}