#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct TYPE_8__ {TYPE_3__* replyBody; int /*<<< orphan*/ * msgBody; int /*<<< orphan*/  msgId; } ;
typedef  TYPE_1__ t_QmIpcReply ;
typedef  TYPE_1__ t_QmIpcMsg ;
struct TYPE_9__ {int fqid; int size; } ;
typedef  TYPE_3__ t_QmIpcFqidParams ;
struct TYPE_10__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  h_FqidMm; scalar_t__ h_Session; int /*<<< orphan*/  h_RsrvFqidMm; } ;
typedef  TYPE_4__ t_Qm ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ E_INVALID_VALUE ; 
 scalar_t__ E_OK ; 
 scalar_t__ ILLEGAL_BASE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ MM_Get (int /*<<< orphan*/ ,int,int,char*) ; 
 scalar_t__ MM_GetForce (int /*<<< orphan*/ ,scalar_t__,scalar_t__,char*) ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  QM_FORCE_FQID ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  WARNING ; 
 scalar_t__ XX_IpcSendMessage (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int XX_LockIntrSpinlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

uint32_t QmFqidGet(t_Qm *p_Qm, uint32_t size, uint32_t alignment, bool force, uint32_t base)
{
    uint64_t    ans;
    uint32_t    intFlags;

    intFlags = XX_LockIntrSpinlock(p_Qm->lock);
    if (force)
    {
        ans = MM_GetForce(p_Qm->h_FqidMm,
                          (uint64_t)base,
                          (uint64_t)size,
                          "QM FQID MEM");
        if (ans == ILLEGAL_BASE)
        {
            ans = MM_GetForce(p_Qm->h_RsrvFqidMm,
                              (uint64_t)base,
                              (uint64_t)size,
                              "QM rsrv FQID MEM");
            if (ans == ILLEGAL_BASE)
                ans = base;
            else if (p_Qm->h_Session)
            {
                t_QmIpcMsg              msg;
                t_QmIpcReply            reply;
                uint32_t                replyLength;
                t_QmIpcFqidParams       ipcFqid;
                t_Error                 errCode = E_OK;

                memset(&msg, 0, sizeof(t_QmIpcMsg));
                memset(&reply, 0, sizeof(t_QmIpcReply));
                ipcFqid.fqid        = base;
                ipcFqid.size        = size;
                msg.msgId           = QM_FORCE_FQID;
                memcpy(msg.msgBody, &ipcFqid, sizeof(t_QmIpcFqidParams));
                replyLength = sizeof(uint32_t) + sizeof(uint32_t);
                if ((errCode = XX_IpcSendMessage(p_Qm->h_Session,
                                                 (uint8_t*)&msg,
                                                 sizeof(msg.msgId) + sizeof(t_QmIpcFqidParams),
                                                 (uint8_t*)&reply,
                                                 &replyLength,
                                                 NULL,
                                                 NULL)) != E_OK)
                    REPORT_ERROR(MAJOR, errCode, NO_MSG);
                if (replyLength != (sizeof(uint32_t) + sizeof(uint32_t)))
                   REPORT_ERROR(MAJOR, E_INVALID_VALUE, ("IPC reply length mismatch"));

                if ((errCode != E_OK) ||
                    (replyLength != (sizeof(uint32_t) + sizeof(uint32_t))))
                    ans = ILLEGAL_BASE;
                else
                    memcpy((uint8_t*)&ans, reply.replyBody, sizeof(uint32_t));
            }
            else
            {
                DBG(WARNING, ("No Ipc - can't validate fqid."));
                ans = base;
            }
        }
    }
    else
        ans = MM_Get(p_Qm->h_FqidMm,
                     size,
                     alignment,
                     "QM FQID MEM");
    XX_UnlockIntrSpinlock(p_Qm->lock, intFlags);

    KASSERT(ans < UINT32_MAX, ("Oops, %lx > UINT32_MAX!\n", ans));
    return (uint32_t)ans;
}