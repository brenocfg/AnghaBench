#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_5__ {TYPE_1__* p_FmMacsecRegs; } ;
typedef  TYPE_2__ t_FmMacsec ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_4__ {int /*<<< orphan*/  cfg; } ;

/* Variables and functions */
 int CFG_S0I ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 int GET_UINT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 

t_Error FmMacsecSetPTP(t_Handle h_FmMacsec, bool enable)
{
    t_FmMacsec  *p_FmMacsec = (t_FmMacsec*)h_FmMacsec;
    uint32_t    tmpReg = 0;

    SANITY_CHECK_RETURN_ERROR(p_FmMacsec, E_INVALID_HANDLE);

    tmpReg = GET_UINT32(p_FmMacsec->p_FmMacsecRegs->cfg);
    if (enable && (tmpReg & CFG_S0I))
        RETURN_ERROR(MINOR, E_INVALID_STATE, ("MACSEC already in point-to-point mode"));

    if (enable)
        tmpReg |= CFG_S0I;
    else
        tmpReg &= ~CFG_S0I;
    WRITE_UINT32(p_FmMacsec->p_FmMacsecRegs->cfg, tmpReg);

    return E_OK;
}