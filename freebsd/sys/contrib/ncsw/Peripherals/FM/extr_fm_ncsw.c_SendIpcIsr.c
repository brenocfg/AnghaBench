#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  msgBody; int /*<<< orphan*/  msgId; } ;
typedef  TYPE_2__ t_FmIpcMsg ;
struct TYPE_10__ {size_t pendingReg; int /*<<< orphan*/  boolErr; } ;
typedef  TYPE_3__ t_FmIpcIsr ;
struct TYPE_11__ {scalar_t__ guestId; TYPE_1__* intrMng; scalar_t__* h_IpcSessions; } ;
typedef  TYPE_4__ t_Fm ;
typedef  scalar_t__ t_Error ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  fmIpcIsr ;
struct TYPE_8__ {scalar_t__ guestId; int /*<<< orphan*/  h_SrcHandle; int /*<<< orphan*/  (* f_Isr ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FM_GUEST_ISR ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE ; 
 scalar_t__ XX_IpcSendMessage (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SendIpcIsr(t_Fm *p_Fm, uint32_t macEvent, uint32_t pendingReg)
{
    ASSERT_COND(p_Fm->guestId == NCSW_MASTER_ID);

    if (p_Fm->intrMng[macEvent].guestId == NCSW_MASTER_ID)
        p_Fm->intrMng[macEvent].f_Isr(p_Fm->intrMng[macEvent].h_SrcHandle);

    /* If the MAC is running on guest-partition and we have IPC session with it,
       we inform him about the event through IPC; otherwise, we ignore the event. */
    else if (p_Fm->h_IpcSessions[p_Fm->intrMng[macEvent].guestId])
    {
        t_Error     err;
        t_FmIpcIsr  fmIpcIsr;
        t_FmIpcMsg  msg;

        memset(&msg, 0, sizeof(msg));
        msg.msgId = FM_GUEST_ISR;
        fmIpcIsr.pendingReg = pendingReg;
        fmIpcIsr.boolErr = FALSE;
        memcpy(msg.msgBody, &fmIpcIsr, sizeof(fmIpcIsr));
        err = XX_IpcSendMessage(p_Fm->h_IpcSessions[p_Fm->intrMng[macEvent].guestId],
                                (uint8_t*)&msg,
                                sizeof(msg.msgId) + sizeof(fmIpcIsr),
                                NULL,
                                NULL,
                                NULL,
                                NULL);
        if (err != E_OK)
            REPORT_ERROR(MINOR, err, NO_MSG);
    }
    else
        DBG(TRACE, ("FM Guest mode, without IPC - can't call ISR!"));
}