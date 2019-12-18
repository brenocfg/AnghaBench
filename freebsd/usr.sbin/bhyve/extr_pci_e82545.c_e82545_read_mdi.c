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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct e82545_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,int) ; 
 int E82545_REVISION_4 ; 
 int M88E1011_I_PHY_ID ; 
 int MII_SR_AUTONEG_CAPS ; 
 int MII_SR_AUTONEG_COMPLETE ; 
 int MII_SR_LINK_STATUS ; 
 int NWAY_AR_SELECTOR_FIELD ; 
#define  PHY_1000T_STATUS 133 
#define  PHY_AUTONEG_ADV 132 
#define  PHY_ID1 131 
#define  PHY_ID2 130 
#define  PHY_LP_ABILITY 129 
#define  PHY_STATUS 128 
 int SR_1000T_LOCAL_RX_STATUS ; 
 int SR_1000T_LP_FD_CAPS ; 
 int SR_1000T_REMOTE_RX_STATUS ; 

__attribute__((used)) static uint32_t
e82545_read_mdi(struct e82545_softc *sc, uint8_t reg_addr,
			uint8_t phy_addr)
{
	//DPRINTF("Read mdi reg:0x%x phy:0x%x\r\n", reg_addr, phy_addr);
	switch (reg_addr) {
	case PHY_STATUS:
		return (MII_SR_LINK_STATUS | MII_SR_AUTONEG_CAPS |
			MII_SR_AUTONEG_COMPLETE);
	case PHY_AUTONEG_ADV:
		return NWAY_AR_SELECTOR_FIELD;
	case PHY_LP_ABILITY:
		return 0;
	case PHY_1000T_STATUS:
		return (SR_1000T_LP_FD_CAPS | SR_1000T_REMOTE_RX_STATUS |
			SR_1000T_LOCAL_RX_STATUS);
	case PHY_ID1:
		return (M88E1011_I_PHY_ID >> 16) & 0xFFFF;
	case PHY_ID2:
		return (M88E1011_I_PHY_ID | E82545_REVISION_4) & 0xFFFF;
	default:
		DPRINTF("Unknown mdi read reg:0x%x phy:0x%x\r\n", reg_addr, phy_addr);
		return 0;
	}
	/* not reached */
}