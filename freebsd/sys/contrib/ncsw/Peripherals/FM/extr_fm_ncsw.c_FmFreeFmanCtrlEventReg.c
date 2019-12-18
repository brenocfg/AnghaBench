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
typedef  size_t uint8_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_5__ {size_t* msgBody; int /*<<< orphan*/  msgId; } ;
typedef  TYPE_1__ t_FmIpcMsg ;
struct TYPE_6__ {scalar_t__ guestId; int /*<<< orphan*/ * usedEventRegs; scalar_t__* h_IpcSessions; } ;
typedef  TYPE_2__ t_Fm ;
typedef  scalar_t__ t_Error ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  eventId ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 scalar_t__ E_NOT_SUPPORTED ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FM_FREE_FMAN_CTRL_EVENT_REG ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XX_IpcSendMessage (scalar_t__,size_t*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void FmFreeFmanCtrlEventReg(t_Handle h_Fm, uint8_t eventId)
{
    t_Fm        *p_Fm = (t_Fm*)h_Fm;

    SANITY_CHECK_RETURN(p_Fm, E_INVALID_HANDLE);

    if ((p_Fm->guestId != NCSW_MASTER_ID) &&
        p_Fm->h_IpcSessions[0])
    {
        t_Error     err;
        t_FmIpcMsg  msg;

        memset(&msg, 0, sizeof(msg));
        msg.msgId = FM_FREE_FMAN_CTRL_EVENT_REG;
        msg.msgBody[0] = eventId;
        err = XX_IpcSendMessage(p_Fm->h_IpcSessions[0],
                                (uint8_t*)&msg,
                                sizeof(msg.msgId)+sizeof(eventId),
                                NULL,
                                NULL,
                                NULL,
                                NULL);
        if (err != E_OK)
            REPORT_ERROR(MINOR, err, NO_MSG);
        return;
    }
    else if (p_Fm->guestId != NCSW_MASTER_ID)
    {
        REPORT_ERROR(MINOR, E_NOT_SUPPORTED,
                     ("running in guest-mode without IPC!"));
        return;
    }

    ((t_Fm*)h_Fm)->usedEventRegs[eventId] = FALSE;
}