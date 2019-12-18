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
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_11__ {scalar_t__ error; int /*<<< orphan*/  msgBody; int /*<<< orphan*/  msgId; } ;
typedef  TYPE_3__ t_FmIpcReply ;
typedef  TYPE_3__ t_FmIpcMsg ;
struct TYPE_12__ {int enumType; int /*<<< orphan*/  id; } ;
typedef  TYPE_5__ t_FmIpcMacParams ;
struct TYPE_13__ {scalar_t__ guestId; int /*<<< orphan*/  baseAddr; scalar_t__* h_IpcSessions; TYPE_2__* p_FmStateStruct; struct fman_fpm_regs* p_FmFpmRegs; } ;
typedef  TYPE_6__ t_Fm ;
typedef  int t_Error ;
struct fman_fpm_regs {int dummy; } ;
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  macParams ;
typedef  scalar_t__ e_FmMacType ;
struct TYPE_9__ {int majorRev; } ;
struct TYPE_10__ {TYPE_1__ revInfo; } ;

/* Variables and functions */
 int EBUSY ; 
 int ERROR_CODE (int /*<<< orphan*/ ) ; 
 int E_INVALID_VALUE ; 
 int E_NOT_SUPPORTED ; 
 int E_OK ; 
 int /*<<< orphan*/  E_TIMEOUT ; 
 int /*<<< orphan*/  FM_RESET_MAC ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int,char*) ; 
 int XX_IpcSendMessage (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ e_FM_MAC_10G ; 
 scalar_t__ fman_reset_mac (struct fman_fpm_regs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

t_Error FmResetMac(t_Handle h_Fm, e_FmMacType type, uint8_t macId)
{
    t_Fm                *p_Fm = (t_Fm*)h_Fm;
    t_Error             err;
    struct fman_fpm_regs *fpm_rg = p_Fm->p_FmFpmRegs;

#if (DPAA_VERSION >= 11)
    if (p_Fm->p_FmStateStruct->revInfo.majorRev >= 6)
        RETURN_ERROR(MINOR, E_NOT_SUPPORTED,
                     ("FMan MAC reset!"));
#endif /*(DPAA_VERSION >= 11)*/

    if ((p_Fm->guestId != NCSW_MASTER_ID) &&
        !p_Fm->baseAddr &&
        p_Fm->h_IpcSessions[0])
    {
        t_FmIpcMacParams    macParams;
        t_FmIpcMsg          msg;
        t_FmIpcReply        reply;
        uint32_t            replyLength;

        memset(&msg, 0, sizeof(msg));
        memset(&reply, 0, sizeof(reply));
        macParams.id = macId;
        macParams.enumType = (uint32_t)type;
        msg.msgId = FM_RESET_MAC;
        memcpy(msg.msgBody,  &macParams, sizeof(macParams));
        replyLength = sizeof(uint32_t);
        err = XX_IpcSendMessage(p_Fm->h_IpcSessions[0],
                                (uint8_t*)&msg,
                                sizeof(msg.msgId)+sizeof(macParams),
                                (uint8_t*)&reply,
                                &replyLength,
                                NULL,
                                NULL);
        if (err != E_OK)
            RETURN_ERROR(MINOR, err, NO_MSG);
        if (replyLength != sizeof(uint32_t))
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("IPC reply length mismatch"));
        return (t_Error)(reply.error);
    }
    else if (!p_Fm->baseAddr)
        RETURN_ERROR(MINOR, E_NOT_SUPPORTED,
                     ("Either IPC or 'baseAddress' is required!"));

    err = (t_Error)fman_reset_mac(fpm_rg, macId, !!(type == e_FM_MAC_10G));

    if (err == -EBUSY)
        return ERROR_CODE(E_TIMEOUT);
    else if (err)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Illegal MAC ID"));

    return E_OK;
}