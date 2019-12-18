#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_7__ {int /*<<< orphan*/  msgId; } ;
typedef  TYPE_2__ t_FmIpcMsg ;
struct TYPE_8__ {scalar_t__ guestId; TYPE_1__* p_FmStateStruct; int /*<<< orphan*/ * h_IpcSessions; struct fman_fpm_regs* p_FmFpmRegs; } ;
typedef  TYPE_3__ t_Fm ;
typedef  scalar_t__ t_Error ;
struct fman_fpm_regs {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_6__ {void* ramsEccEnable; scalar_t__ internalCall; void* explicitEnable; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 scalar_t__ E_OK ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FM_ENABLE_RAM_ECC ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 scalar_t__ XX_IpcSendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fman_enable_rams_ecc (struct fman_fpm_regs*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

t_Error FM_EnableRamsEcc(t_Handle h_Fm)
{
    t_Fm        *p_Fm = (t_Fm*)h_Fm;
    struct fman_fpm_regs *fpm_rg;

    SANITY_CHECK_RETURN_ERROR(p_Fm, E_INVALID_HANDLE);

    fpm_rg = p_Fm->p_FmFpmRegs;

    if (p_Fm->guestId != NCSW_MASTER_ID)
    {
        t_FmIpcMsg      msg;
        t_Error         err;

        memset(&msg, 0, sizeof(msg));
        msg.msgId = FM_ENABLE_RAM_ECC;
        err = XX_IpcSendMessage(p_Fm->h_IpcSessions[0],
                                (uint8_t*)&msg,
                                sizeof(msg.msgId),
                                NULL,
                                NULL,
                                NULL,
                                NULL);
        if (err != E_OK)
            RETURN_ERROR(MINOR, err, NO_MSG);
        return E_OK;
    }

    if (!p_Fm->p_FmStateStruct->internalCall)
        p_Fm->p_FmStateStruct->explicitEnable = TRUE;
    p_Fm->p_FmStateStruct->internalCall = FALSE;

    if (p_Fm->p_FmStateStruct->ramsEccEnable)
        return E_OK;
    else
    {
        fman_enable_rams_ecc(fpm_rg);
        p_Fm->p_FmStateStruct->ramsEccEnable = TRUE;
    }

    return E_OK;
}