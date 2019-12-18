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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  enetMode; struct TYPE_4__* p_MiiMemMap; } ;
typedef  TYPE_1__ t_Memac ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  enum enet_speed { ____Placeholder_enet_speed } enet_speed ;

/* Variables and functions */
 scalar_t__ ENET_SPEED_FROM_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fman_memac_mii_write_phy_reg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

t_Error MEMAC_MII_WritePhyReg(t_Handle  h_Memac,
                             uint8_t    phyAddr,
                             uint8_t    reg,
                             uint16_t   data)
{
    t_Memac                 *p_Memac = (t_Memac *)h_Memac;

    SANITY_CHECK_RETURN_ERROR(p_Memac, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_Memac->p_MiiMemMap, E_INVALID_HANDLE);

    return (t_Error)fman_memac_mii_write_phy_reg(p_Memac->p_MiiMemMap,
                                                 phyAddr,
                                                 reg,
                                                 data,
                                                 (enum enet_speed)ENET_SPEED_FROM_MODE(p_Memac->enetMode));
}