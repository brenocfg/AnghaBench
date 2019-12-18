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
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int t_Handle ;
struct TYPE_8__ {scalar_t__ guestId; scalar_t__ event; } ;
typedef  TYPE_2__ t_FmIpcRegisterIntr ;
struct TYPE_9__ {int /*<<< orphan*/  msgBody; int /*<<< orphan*/  msgId; } ;
typedef  TYPE_3__ t_FmIpcMsg ;
struct TYPE_10__ {scalar_t__ guestId; scalar_t__* h_IpcSessions; TYPE_1__* intrMng; } ;
typedef  TYPE_4__ t_Fm ;
typedef  scalar_t__ t_Error ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  fmIpcRegisterIntr ;
typedef  int /*<<< orphan*/  e_FmIntrType ;
typedef  int /*<<< orphan*/  e_FmEventModules ;
struct TYPE_7__ {void (* f_Isr ) (int) ;int h_SrcHandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 scalar_t__ E_NOT_SUPPORTED ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FM_REGISTER_INTR ; 
 int /*<<< orphan*/  GET_FM_MODULE_EVENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ XX_IpcSendMessage (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int e_FM_EV_DUMMY_LAST ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void FmRegisterIntr(t_Handle                h_Fm,
                    e_FmEventModules        module,
                    uint8_t                 modId,
                    e_FmIntrType            intrType,
                    void                    (*f_Isr) (t_Handle h_Arg),
                    t_Handle                h_Arg)
{
    t_Fm                *p_Fm = (t_Fm*)h_Fm;
    int                 event = 0;

    ASSERT_COND(h_Fm);

    GET_FM_MODULE_EVENT(module, modId, intrType, event);
    ASSERT_COND(event < e_FM_EV_DUMMY_LAST);

    /* register in local FM structure */
    p_Fm->intrMng[event].f_Isr = f_Isr;
    p_Fm->intrMng[event].h_SrcHandle = h_Arg;

    if ((p_Fm->guestId != NCSW_MASTER_ID) &&
        p_Fm->h_IpcSessions[0])
    {
        t_FmIpcRegisterIntr fmIpcRegisterIntr;
        t_Error             err;
        t_FmIpcMsg          msg;

        /* register in Master FM structure */
        fmIpcRegisterIntr.event = (uint32_t)event;
        fmIpcRegisterIntr.guestId = p_Fm->guestId;
        memset(&msg, 0, sizeof(msg));
        msg.msgId = FM_REGISTER_INTR;
        memcpy(msg.msgBody, &fmIpcRegisterIntr, sizeof(fmIpcRegisterIntr));
        err = XX_IpcSendMessage(p_Fm->h_IpcSessions[0],
                                (uint8_t*)&msg,
                                sizeof(msg.msgId) + sizeof(fmIpcRegisterIntr),
                                NULL,
                                NULL,
                                NULL,
                                NULL);
        if (err != E_OK)
            REPORT_ERROR(MINOR, err, NO_MSG);
    }
    else if (p_Fm->guestId != NCSW_MASTER_ID)
        REPORT_ERROR(MINOR, E_NOT_SUPPORTED,
                     ("running in guest-mode without IPC!"));
}