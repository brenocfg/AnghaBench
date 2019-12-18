#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  enetMode; } ;
typedef  TYPE_1__ t_Memac ;
typedef  int /*<<< orphan*/  e_EnetMode ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_INTERFACE_FROM_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE_ENET_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMAC_MII_WritePhyReg (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int PHY_SGMII_CR_DEF_VAL ; 
 int PHY_SGMII_CR_RESET_AN ; 
 int PHY_SGMII_DEV_ABILITY_1000X ; 
 int PHY_SGMII_IF_MODE_1000X ; 
 int /*<<< orphan*/  e_ENET_SPEED_1000 ; 

__attribute__((used)) static void SetupSgmiiInternalPhyBaseX(t_Memac *p_Memac, uint8_t phyAddr)
{
    uint16_t    tmpReg16;
    e_EnetMode  enetMode;

     /* In case the higher MACs are used (i.e. the MACs that should support 10G),
        speed=10000 is provided for SGMII ports. Temporary modify enet mode
        to 1G one, so MII functions can work correctly. */
    enetMode = p_Memac->enetMode;
    p_Memac->enetMode = MAKE_ENET_MODE(ENET_INTERFACE_FROM_MODE(p_Memac->enetMode), e_ENET_SPEED_1000);

    /* 1000BaseX mode */
    tmpReg16 = PHY_SGMII_IF_MODE_1000X;
    MEMAC_MII_WritePhyReg(p_Memac, phyAddr, 0x14, tmpReg16);

    /* AN Device capability  */
    tmpReg16 = PHY_SGMII_DEV_ABILITY_1000X;
    MEMAC_MII_WritePhyReg(p_Memac, phyAddr, 0x4, tmpReg16);

    /* Adjust link timer for SGMII  -
       For Serdes 1000BaseX auto-negotiation the timer should be 10 ms.
       The link_timer register is configured in units of the clock.
       - When running as 1G SGMII, Serdes clock is 125 MHz, so
         unit = 1 / (125*10^6 Hz) = 8 ns.
         10 ms in units of 8 ns = 10ms / 8ns = 1250000 = 0x1312d0
       - When running as 2.5G SGMII, Serdes clock is 312.5 MHz, so
         unit = 1 / (312.5*10^6 Hz) = 3.2 ns.
         10 ms in units of 3.2 ns = 10ms / 3.2ns = 3125000 = 0x2faf08.
       Since link_timer value of 1G SGMII will be too short for 2.5 SGMII,
       we always set up here a value of 2.5 SGMII. */
    MEMAC_MII_WritePhyReg(p_Memac, phyAddr, 0x13, 0x002f);
    MEMAC_MII_WritePhyReg(p_Memac, phyAddr, 0x12, 0xaf08);

    /* Restart AN */
    tmpReg16 = PHY_SGMII_CR_DEF_VAL | PHY_SGMII_CR_RESET_AN;
    MEMAC_MII_WritePhyReg(p_Memac, phyAddr, 0x0, tmpReg16);

    /* Restore original enet mode */
    p_Memac->enetMode = enetMode;
}