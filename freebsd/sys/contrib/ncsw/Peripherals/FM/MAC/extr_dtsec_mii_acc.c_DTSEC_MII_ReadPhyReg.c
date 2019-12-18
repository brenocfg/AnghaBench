#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  scalar_t__ t_Handle ;
typedef  scalar_t__ t_Error ;
struct TYPE_2__ {int clkFreq; } ;
struct dtsec_mii_reg {struct dtsec_mii_reg* p_MiiMemMap; TYPE_1__ fmMacControllerDriver; } ;
typedef  struct dtsec_mii_reg t_Dtsec ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 scalar_t__ E_NO_DEVICE ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  MINOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (struct dtsec_mii_reg*,int /*<<< orphan*/ ) ; 
 scalar_t__ fman_dtsec_mii_read_reg (struct dtsec_mii_reg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

t_Error DTSEC_MII_ReadPhyReg(t_Handle h_Dtsec,
                             uint8_t  phyAddr,
                             uint8_t  reg,
                             uint16_t *p_Data)
{
    t_Dtsec               *p_Dtsec = (t_Dtsec *)h_Dtsec;
    struct dtsec_mii_reg  *miiregs;
    uint16_t               dtsec_freq;
    t_Error                    err;

    SANITY_CHECK_RETURN_ERROR(p_Dtsec, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_Dtsec->p_MiiMemMap, E_INVALID_HANDLE);

    dtsec_freq = (uint16_t)(p_Dtsec->fmMacControllerDriver.clkFreq >> 1);
    miiregs = p_Dtsec->p_MiiMemMap;

    err = fman_dtsec_mii_read_reg(miiregs, phyAddr, reg, p_Data, dtsec_freq);

    if (*p_Data == 0xffff)
        RETURN_ERROR(MINOR, E_NO_DEVICE,
                     ("Read wrong data (0xffff): phyAddr 0x%x, reg 0x%x",
                      phyAddr, reg));
    if (err)
        RETURN_ERROR(MINOR, (t_Error)err, NO_MSG);

    return E_OK;
}