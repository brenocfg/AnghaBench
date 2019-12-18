#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_9__ {int /*<<< orphan*/  replyBody; int /*<<< orphan*/  msgId; } ;
typedef  TYPE_3__ t_FmIpcReply ;
typedef  TYPE_3__ t_FmIpcMsg ;
struct TYPE_10__ {scalar_t__ guestId; TYPE_2__* p_FmStateStruct; TYPE_1__* p_FmFpmRegs; scalar_t__ baseAddr; scalar_t__* h_IpcSessions; } ;
typedef  TYPE_5__ t_Fm ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_8__ {int count1MicroBit; } ;
struct TYPE_7__ {int /*<<< orphan*/  fmfp_tsc1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FM_GET_TIMESTAMP_SCALE ; 
 int FPM_TS_CTL_EN ; 
 int GET_UINT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  XX_IpcSendMessage (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

uint32_t FmGetTimeStampScale(t_Handle h_Fm)
{
    t_Fm                *p_Fm = (t_Fm*)h_Fm;

    if ((p_Fm->guestId != NCSW_MASTER_ID) &&
        !p_Fm->baseAddr &&
        p_Fm->h_IpcSessions[0])
    {
        t_Error             err;
        t_FmIpcMsg          msg;
        t_FmIpcReply        reply;
        uint32_t            replyLength, timeStamp;

        memset(&msg, 0, sizeof(msg));
        memset(&reply, 0, sizeof(reply));
        msg.msgId = FM_GET_TIMESTAMP_SCALE;
        replyLength = sizeof(uint32_t) + sizeof(uint32_t);
        if ((err = XX_IpcSendMessage(p_Fm->h_IpcSessions[0],
                                     (uint8_t*)&msg,
                                     sizeof(msg.msgId),
                                     (uint8_t*)&reply,
                                     &replyLength,
                                     NULL,
                                     NULL)) != E_OK)
        {
            REPORT_ERROR(MAJOR, err, NO_MSG);
            return 0;
        }
        if (replyLength != (sizeof(uint32_t) + sizeof(uint32_t)))
        {
            REPORT_ERROR(MAJOR, E_INVALID_VALUE, ("IPC reply length mismatch"));
            return 0;
        }

        memcpy((uint8_t*)&timeStamp, reply.replyBody, sizeof(uint32_t));
        return timeStamp;
    }
    else if ((p_Fm->guestId != NCSW_MASTER_ID) &&
             p_Fm->baseAddr)
    {
        if (!(GET_UINT32(p_Fm->p_FmFpmRegs->fmfp_tsc1) & FPM_TS_CTL_EN))
        {
            REPORT_ERROR(MAJOR, E_INVALID_STATE, ("timestamp is not enabled!"));
            return 0;
        }
    }
    else if (p_Fm->guestId != NCSW_MASTER_ID)
        DBG(WARNING, ("No IPC - can't validate FM if timestamp enabled."));

    return p_Fm->p_FmStateStruct->count1MicroBit;
}