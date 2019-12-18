#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_10__ {int /*<<< orphan*/  error; int /*<<< orphan*/  replyBody; int /*<<< orphan*/  msgId; } ;
typedef  TYPE_1__ t_FmIpcReply ;
typedef  TYPE_1__ t_FmIpcMsg ;
struct TYPE_11__ {void* minorRev; void* majorRev; scalar_t__ packageRev; } ;
typedef  TYPE_3__ t_FmIpcFmanCtrlCodeRevisionInfo ;
struct TYPE_12__ {scalar_t__ guestId; void* minorRev; void* majorRev; scalar_t__ packageRev; scalar_t__ baseAddr; scalar_t__* h_IpcSessions; } ;
typedef  TYPE_4__ t_FmCtrlCodeRevisionInfo ;
typedef  TYPE_4__ t_Fm ;
struct TYPE_13__ {int /*<<< orphan*/  idata; int /*<<< orphan*/  iadd; } ;
typedef  TYPE_6__ t_FMIramRegs ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  E_NULL_POINTER ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FM_GET_FMAN_CTRL_CODE_REV ; 
 scalar_t__ FM_MM_IMEM ; 
 int GET_UINT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ UINT_TO_PTR (scalar_t__) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XX_IpcSendMessage (scalar_t__,void**,int,void**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

t_Error FM_GetFmanCtrlCodeRevision(t_Handle h_Fm, t_FmCtrlCodeRevisionInfo *p_RevisionInfo)
{
    t_Fm                            *p_Fm = (t_Fm*)h_Fm;
    t_FMIramRegs                    *p_Iram;
    uint32_t                        revInfo;

    SANITY_CHECK_RETURN_ERROR(p_Fm, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_RevisionInfo, E_NULL_POINTER);

    if ((p_Fm->guestId != NCSW_MASTER_ID) &&
        p_Fm->h_IpcSessions[0])
    {
        t_Error                         err;
        t_FmIpcMsg                      msg;
        t_FmIpcReply                    reply;
        uint32_t                        replyLength;
        t_FmIpcFmanCtrlCodeRevisionInfo ipcRevInfo;

        memset(&msg, 0, sizeof(msg));
        memset(&reply, 0, sizeof(reply));
        msg.msgId = FM_GET_FMAN_CTRL_CODE_REV;
        replyLength = sizeof(uint32_t) + sizeof(t_FmCtrlCodeRevisionInfo);
        if ((err = XX_IpcSendMessage(p_Fm->h_IpcSessions[0],
                                     (uint8_t*)&msg,
                                     sizeof(msg.msgId),
                                     (uint8_t*)&reply,
                                     &replyLength,
                                     NULL,
                                     NULL)) != E_OK)
            RETURN_ERROR(MINOR, err, NO_MSG);
        if (replyLength != (sizeof(uint32_t) + sizeof(t_FmCtrlCodeRevisionInfo)))
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("IPC reply length mismatch"));
        memcpy((uint8_t*)&ipcRevInfo, reply.replyBody, sizeof(t_FmCtrlCodeRevisionInfo));
        p_RevisionInfo->packageRev = ipcRevInfo.packageRev;
        p_RevisionInfo->majorRev = ipcRevInfo.majorRev;
        p_RevisionInfo->minorRev = ipcRevInfo.minorRev;
        return (t_Error)(reply.error);
    }
    else if (p_Fm->guestId != NCSW_MASTER_ID)
        RETURN_ERROR(MINOR, E_NOT_SUPPORTED,
                     ("running in guest-mode without IPC!"));

    p_Iram = (t_FMIramRegs *)UINT_TO_PTR(p_Fm->baseAddr + FM_MM_IMEM);
    WRITE_UINT32(p_Iram->iadd, 0x4);
    while (GET_UINT32(p_Iram->iadd) != 0x4) ;
    revInfo = GET_UINT32(p_Iram->idata);
    p_RevisionInfo->packageRev = (uint16_t)((revInfo & 0xFFFF0000) >> 16);
    p_RevisionInfo->majorRev = (uint8_t)((revInfo & 0x0000FF00) >> 8);
    p_RevisionInfo->minorRev = (uint8_t)(revInfo & 0x000000FF);

    return E_OK;
}