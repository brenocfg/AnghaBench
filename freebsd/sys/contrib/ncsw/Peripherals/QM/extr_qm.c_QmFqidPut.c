#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  msgBody; int /*<<< orphan*/  msgId; } ;
typedef  TYPE_1__ t_QmIpcMsg ;
struct TYPE_8__ {scalar_t__ size; scalar_t__ fqid; } ;
typedef  TYPE_2__ t_QmIpcFqidParams ;
struct TYPE_9__ {int /*<<< orphan*/  lock; scalar_t__ h_Session; int /*<<< orphan*/  h_FqidMm; int /*<<< orphan*/  h_RsrvFqidMm; } ;
typedef  TYPE_3__ t_Qm ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_NOT_FOUND ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ ILLEGAL_BASE ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ MM_GetForce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ MM_InRange (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MM_Put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MM_PutForce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  QM_PUT_FQID ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  XX_IpcSendMessage (scalar_t__,scalar_t__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XX_LockIntrSpinlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

t_Error QmFqidPut(t_Qm *p_Qm, uint32_t base)
{
    uint32_t    intFlags;

    intFlags = XX_LockIntrSpinlock(p_Qm->lock);
    /* Check maybe this fqid was reserved in the past */
    if (MM_GetForce(p_Qm->h_RsrvFqidMm,
                    (uint64_t)base,
                    (uint64_t)1,
                    "QM rsrv FQID MEM") == ILLEGAL_BASE)
    {
        XX_UnlockIntrSpinlock(p_Qm->lock, intFlags);
        return E_OK;
    }
    else
        MM_PutForce(p_Qm->h_RsrvFqidMm,
                    (uint64_t)base,
                    (uint64_t)1);
    if (MM_InRange(p_Qm->h_FqidMm, (uint64_t)base))
    {
        if (MM_Put(p_Qm->h_FqidMm, (uint64_t)base) != 0)
        {
            XX_UnlockIntrSpinlock(p_Qm->lock, intFlags);
            return E_OK;
        }
        else
        {
            XX_UnlockIntrSpinlock(p_Qm->lock, intFlags);
            return ERROR_CODE(E_NOT_FOUND);
        }
    }
    else if (p_Qm->h_Session)
    {
        t_QmIpcMsg              msg;
        t_QmIpcFqidParams       ipcFqid;
        t_Error                 errCode = E_OK;

        memset(&msg, 0, sizeof(t_QmIpcMsg));
        ipcFqid.fqid        = (uint8_t)base;
        ipcFqid.size        = 0;
        msg.msgId           = QM_PUT_FQID;
        memcpy(msg.msgBody, &ipcFqid, sizeof(t_QmIpcFqidParams));
        if ((errCode = XX_IpcSendMessage(p_Qm->h_Session,
                                         (uint8_t*)&msg,
                                         sizeof(msg.msgId) + sizeof(t_QmIpcFqidParams),
                                         NULL,
                                         NULL,
                                         NULL,
                                         NULL)) != E_OK)
        {
            XX_UnlockIntrSpinlock(p_Qm->lock, intFlags);
            RETURN_ERROR(MAJOR, errCode, NO_MSG);
        }
    }
    else
        DBG(WARNING, ("No Ipc - can't validate fqid."));
    XX_UnlockIntrSpinlock(p_Qm->lock, intFlags);

    return E_OK;
}