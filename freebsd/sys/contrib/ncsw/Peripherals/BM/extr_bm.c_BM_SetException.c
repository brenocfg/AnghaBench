#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_6__ {scalar_t__ guestId; TYPE_1__* p_BmRegs; } ;
typedef  TYPE_2__ t_Bm ;
typedef  int /*<<< orphan*/  e_BmExceptions ;
struct TYPE_5__ {int /*<<< orphan*/  err_ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_ConfigException (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_OPERATION ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  GET_UINT32 (int /*<<< orphan*/ ) ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

t_Error BM_SetException(t_Handle h_Bm, e_BmExceptions exception, bool enable)
{
    t_Bm                *p_Bm = (t_Bm*)h_Bm;
    uint32_t            tmpReg, bitMask = 0;

    SANITY_CHECK_RETURN_ERROR(p_Bm, E_INVALID_HANDLE);

    if (p_Bm->guestId != NCSW_MASTER_ID)
        RETURN_ERROR(WARNING, E_INVALID_OPERATION, ("Master Only"));

    BM_ConfigException(p_Bm, exception, enable);

    tmpReg = GET_UINT32(p_Bm->p_BmRegs->err_ier);

    if(enable)
        tmpReg |= bitMask;
    else
        tmpReg &= ~bitMask;
    WRITE_UINT32(p_Bm->p_BmRegs->err_ier, tmpReg);

    return E_OK;
}