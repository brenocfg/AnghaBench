#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct TYPE_10__ {int /*<<< orphan*/ * fmpl_pmr; } ;
typedef  TYPE_2__ t_FmPcdPlcrRegs ;
struct TYPE_11__ {int guestId; int /*<<< orphan*/  msgBody; int /*<<< orphan*/  msgId; void* base; void* num; } ;
typedef  TYPE_3__ t_FmPcdIpcMsg ;
struct TYPE_12__ {scalar_t__ guestId; scalar_t__ h_IpcSession; TYPE_1__* p_FmPcdPlcr; } ;
typedef  TYPE_4__ t_FmPcd ;
typedef  TYPE_3__ t_FmIpcResourceAllocParams ;
typedef  scalar_t__ t_Error ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_9__ {TYPE_2__* p_FmPcdPlcrRegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int /*<<< orphan*/ ) ; 
 scalar_t__ E_INVALID_VALUE ; 
 scalar_t__ E_NOT_SUPPORTED ; 
 scalar_t__ E_OK ; 
 int FM_PCD_PLCR_PMR_V ; 
 int /*<<< orphan*/  FM_PCD_SET_PORT_PROFILES ; 
 int GET_UINT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IN_RANGE (int,int,int) ; 
 int /*<<< orphan*/  LOG2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XX_IpcSendMessage (scalar_t__,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

t_Error PlcrSetPortProfiles(t_FmPcd    *p_FmPcd,
                            uint8_t    hardwarePortId,
                            uint16_t   numOfProfiles,
                            uint16_t   base)
{
    t_FmPcdPlcrRegs *p_Regs = p_FmPcd->p_FmPcdPlcr->p_FmPcdPlcrRegs;
    uint32_t        log2Num, tmpReg32;

    if ((p_FmPcd->guestId != NCSW_MASTER_ID) &&
        !p_Regs &&
        p_FmPcd->h_IpcSession)
    {
        t_FmIpcResourceAllocParams      ipcAllocParams;
        t_FmPcdIpcMsg                   msg;
        t_Error                         err;

        memset(&msg, 0, sizeof(msg));
        memset(&ipcAllocParams, 0, sizeof(t_FmIpcResourceAllocParams));
        ipcAllocParams.guestId         = hardwarePortId;
        ipcAllocParams.num             = numOfProfiles;
        ipcAllocParams.base            = base;
        msg.msgId                              = FM_PCD_SET_PORT_PROFILES;
        memcpy(msg.msgBody, &ipcAllocParams, sizeof(t_FmIpcResourceAllocParams));
        err = XX_IpcSendMessage(p_FmPcd->h_IpcSession,
                                (uint8_t*)&msg,
                                sizeof(msg.msgId) + sizeof(t_FmIpcResourceAllocParams),
                                NULL,
                                NULL,
                                NULL,
                                NULL);
        if (err != E_OK)
            RETURN_ERROR(MAJOR, err, NO_MSG);
        return E_OK;
    }
    else if (!p_Regs)
        RETURN_ERROR(MINOR, E_NOT_SUPPORTED,
                     ("Either IPC or 'baseAddress' is required!"));

    ASSERT_COND(IN_RANGE(1, hardwarePortId, 63));

    if (GET_UINT32(p_Regs->fmpl_pmr[hardwarePortId-1]) & FM_PCD_PLCR_PMR_V)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE,
                     ("The requesting port has already an allocated profiles window."));

    /**********************FMPL_PMRx******************/
    LOG2((uint64_t)numOfProfiles, log2Num);
    tmpReg32 = base;
    tmpReg32 |= log2Num << 16;
    tmpReg32 |= FM_PCD_PLCR_PMR_V;
    WRITE_UINT32(p_Regs->fmpl_pmr[hardwarePortId-1], tmpReg32);

    return E_OK;
}