#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_18__ {int* msgBody; scalar_t__ replyBody; int /*<<< orphan*/  msgId; } ;
typedef  TYPE_1__ t_FmPcdIpcReply ;
typedef  TYPE_1__ t_FmPcdIpcMsg ;
struct TYPE_19__ {int guestId; int /*<<< orphan*/  h_Fm; struct TYPE_19__* p_FmPcdDriverParam; void* capwapFrameIdAddr; int /*<<< orphan*/  h_FmMuram; void* ipv6FrameIdAddr; TYPE_1__* fmPcdModuleName; scalar_t__ p_FmPcdPrs; scalar_t__ p_FmPcdPlcr; scalar_t__ p_FmPcdKg; scalar_t__ h_IpcSession; TYPE_1__* fmPcdIpcHandlerModuleName; int /*<<< orphan*/  fmRevInfo; } ;
typedef  TYPE_3__ t_FmPcd ;
typedef  scalar_t__ t_Error ;
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  isMasterAlive ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_INIT_PARAMETERS (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckFmPcdParameters ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 scalar_t__ E_INVALID_STATE ; 
 scalar_t__ E_INVALID_VALUE ; 
 scalar_t__ E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FM_GetRevision (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FM_MURAM_AllocMem (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  FM_PCD_Free (TYPE_3__*) ; 
 int /*<<< orphan*/  FM_PCD_MASTER_IS_ALIVE ; 
 int /*<<< orphan*/  FM_PCD_MAX_REPLY_SIZE ; 
 int /*<<< orphan*/  FmGetId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmRegisterPcd (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  IOMemSet32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IpcMsgCompletionCB ; 
 int /*<<< orphan*/  IpcMsgHandlerCB ; 
 scalar_t__ KgInit (TYPE_3__*) ; 
 int /*<<< orphan*/  MAJOR ; 
 int MODULE_NAME_SIZE ; 
 int NCSW_MASTER_ID ; 
 char* NO_MSG ; 
 void* PTR_TO_UINT (int /*<<< orphan*/ ) ; 
 scalar_t__ PlcrInit (TYPE_3__*) ; 
 scalar_t__ PrsInit (TYPE_3__*) ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int Sprint (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UINT_TO_PTR (void*) ; 
 int /*<<< orphan*/  XX_Free (TYPE_3__*) ; 
 scalar_t__ XX_IpcInitSession (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ XX_IpcRegisterMsgHandler (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XX_IpcSendMessage (scalar_t__,scalar_t__*,int,scalar_t__*,int*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ blockingFlag ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

t_Error FM_PCD_Init(t_Handle h_FmPcd)
{
    t_FmPcd         *p_FmPcd = (t_FmPcd*)h_FmPcd;
    t_Error         err = E_OK;
    t_FmPcdIpcMsg   msg;

    SANITY_CHECK_RETURN_ERROR(p_FmPcd, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_FmPcd->p_FmPcdDriverParam, E_INVALID_HANDLE);

    FM_GetRevision(p_FmPcd->h_Fm, &p_FmPcd->fmRevInfo);

    if (p_FmPcd->guestId != NCSW_MASTER_ID)
    {
        memset(p_FmPcd->fmPcdIpcHandlerModuleName, 0, (sizeof(char)) * MODULE_NAME_SIZE);
        if (Sprint (p_FmPcd->fmPcdIpcHandlerModuleName, "FM_PCD_%d_%d", FmGetId(p_FmPcd->h_Fm), NCSW_MASTER_ID) != 10)
            RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Sprint failed"));
        memset(p_FmPcd->fmPcdModuleName, 0, (sizeof(char)) * MODULE_NAME_SIZE);
        if (Sprint (p_FmPcd->fmPcdModuleName, "FM_PCD_%d_%d",FmGetId(p_FmPcd->h_Fm), p_FmPcd->guestId) != (p_FmPcd->guestId<10 ? 10:11))
            RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Sprint failed"));

        p_FmPcd->h_IpcSession = XX_IpcInitSession(p_FmPcd->fmPcdIpcHandlerModuleName, p_FmPcd->fmPcdModuleName);
        if (p_FmPcd->h_IpcSession)
        {
            t_FmPcdIpcReply         reply;
            uint32_t                replyLength;
            uint8_t                 isMasterAlive = 0;

            memset(&msg, 0, sizeof(msg));
            memset(&reply, 0, sizeof(reply));
            msg.msgId = FM_PCD_MASTER_IS_ALIVE;
            msg.msgBody[0] = p_FmPcd->guestId;
            blockingFlag = TRUE;

            do
            {
                replyLength = sizeof(uint32_t) + sizeof(isMasterAlive);
                if ((err = XX_IpcSendMessage(p_FmPcd->h_IpcSession,
                                             (uint8_t*)&msg,
                                             sizeof(msg.msgId)+sizeof(p_FmPcd->guestId),
                                             (uint8_t*)&reply,
                                             &replyLength,
                                             IpcMsgCompletionCB,
                                             h_FmPcd)) != E_OK)
                    REPORT_ERROR(MAJOR, err, NO_MSG);
                while (blockingFlag) ;
                if (replyLength != (sizeof(uint32_t) + sizeof(isMasterAlive)))
                    REPORT_ERROR(MAJOR, E_INVALID_VALUE, ("IPC reply length mismatch"));
                isMasterAlive = *(uint8_t*)(reply.replyBody);
            } while (!isMasterAlive);
        }
    }

    CHECK_INIT_PARAMETERS(p_FmPcd, CheckFmPcdParameters);

    if (p_FmPcd->p_FmPcdKg)
    {
        err = KgInit(p_FmPcd);
        if (err)
            RETURN_ERROR(MAJOR, err, NO_MSG);
    }

    if (p_FmPcd->p_FmPcdPlcr)
    {
        err = PlcrInit(p_FmPcd);
        if (err)
            RETURN_ERROR(MAJOR, err, NO_MSG);
    }

    if (p_FmPcd->p_FmPcdPrs)
    {
        err = PrsInit(p_FmPcd);
        if (err)
            RETURN_ERROR(MAJOR, err, NO_MSG);
    }

    if (p_FmPcd->guestId == NCSW_MASTER_ID)
    {
         /* register to inter-core messaging mechanism */
        memset(p_FmPcd->fmPcdModuleName, 0, (sizeof(char)) * MODULE_NAME_SIZE);
        if (Sprint (p_FmPcd->fmPcdModuleName, "FM_PCD_%d_%d",FmGetId(p_FmPcd->h_Fm),NCSW_MASTER_ID) != 10)
            RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Sprint failed"));
        err = XX_IpcRegisterMsgHandler(p_FmPcd->fmPcdModuleName, IpcMsgHandlerCB, p_FmPcd, FM_PCD_MAX_REPLY_SIZE);
        if (err)
            RETURN_ERROR(MAJOR, err, NO_MSG);
    }

    /* IPv6 Frame-Id used for fragmentation */
    p_FmPcd->ipv6FrameIdAddr = PTR_TO_UINT(FM_MURAM_AllocMem(p_FmPcd->h_FmMuram, 4, 4));
    if (!p_FmPcd->ipv6FrameIdAddr)
    {
        FM_PCD_Free(p_FmPcd);
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("MURAM allocation for IPv6 Frame-Id"));
    }
    IOMemSet32(UINT_TO_PTR(p_FmPcd->ipv6FrameIdAddr), 0,  4);

    /* CAPWAP Frame-Id used for fragmentation */
    p_FmPcd->capwapFrameIdAddr = PTR_TO_UINT(FM_MURAM_AllocMem(p_FmPcd->h_FmMuram, 2, 4));
    if (!p_FmPcd->capwapFrameIdAddr)
    {
        FM_PCD_Free(p_FmPcd);
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("MURAM allocation for CAPWAP Frame-Id"));
    }
    IOMemSet32(UINT_TO_PTR(p_FmPcd->capwapFrameIdAddr), 0,  2);

    XX_Free(p_FmPcd->p_FmPcdDriverParam);
    p_FmPcd->p_FmPcdDriverParam = NULL;

    FmRegisterPcd(p_FmPcd->h_Fm, p_FmPcd);

    return E_OK;
}