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
typedef  int uint8_t ;
struct TYPE_4__ {int enetMode; } ;
typedef  TYPE_1__ t_Memac ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int ENET_IF_SGMII_BASEX ; 
 scalar_t__ ENET_INTERFACE_FROM_MODE (int) ; 
 int /*<<< orphan*/  E_OK ; 
 int PHY_MDIO_ADDR ; 
 int /*<<< orphan*/  SetupSgmiiInternalPhy (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SetupSgmiiInternalPhyBaseX (TYPE_1__*,int) ; 
 scalar_t__ e_ENET_IF_QSGMII ; 
 scalar_t__ e_ENET_IF_SGMII ; 

__attribute__((used)) static t_Error MemacInitInternalPhy(t_Handle h_Memac)
{
    t_Memac *p_Memac = (t_Memac *)h_Memac;
    uint8_t i, phyAddr;

    if (ENET_INTERFACE_FROM_MODE(p_Memac->enetMode) == e_ENET_IF_SGMII)
    {
        /* Configure internal SGMII PHY */
        if (p_Memac->enetMode & ENET_IF_SGMII_BASEX)
            SetupSgmiiInternalPhyBaseX(p_Memac, PHY_MDIO_ADDR);
        else
            SetupSgmiiInternalPhy(p_Memac, PHY_MDIO_ADDR);
    }
    else if (ENET_INTERFACE_FROM_MODE(p_Memac->enetMode) == e_ENET_IF_QSGMII)
    {
        /* Configure 4 internal SGMII PHYs */
        for (i = 0; i < 4; i++)
        {
            /* QSGMII PHY address occupies 3 upper bits of 5-bit
               phyAddress; the lower 2 bits are used to extend
               register address space and access each one of 4
               ports inside QSGMII. */
            phyAddr = (uint8_t)((PHY_MDIO_ADDR << 2) | i);
            if (p_Memac->enetMode & ENET_IF_SGMII_BASEX)
                SetupSgmiiInternalPhyBaseX(p_Memac, phyAddr);
            else
                SetupSgmiiInternalPhy(p_Memac, phyAddr);
        }
    }
    return E_OK;
}