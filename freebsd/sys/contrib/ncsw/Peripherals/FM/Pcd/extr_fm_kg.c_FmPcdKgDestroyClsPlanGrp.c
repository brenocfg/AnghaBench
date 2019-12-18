#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_FmPcdKgClsPlanGrp ;
struct TYPE_11__ {scalar_t__ error; int /*<<< orphan*/  msgBody; int /*<<< orphan*/  msgId; int /*<<< orphan*/  baseEntry; int /*<<< orphan*/  sizeOfGrp; int /*<<< orphan*/  netEnvId; scalar_t__ owners; } ;
typedef  TYPE_2__ t_FmPcdIpcReply ;
typedef  TYPE_2__ t_FmPcdIpcMsg ;
struct TYPE_12__ {scalar_t__ guestId; int /*<<< orphan*/  clsPlanBase; int /*<<< orphan*/  numOfClsPlanEntries; } ;
typedef  TYPE_4__ t_FmPcdIpcKgClsPlanParams ;
struct TYPE_13__ {scalar_t__ guestId; TYPE_1__* p_FmPcdKg; int /*<<< orphan*/  h_IpcSession; } ;
typedef  TYPE_5__ t_FmPcd ;
typedef  scalar_t__ t_Error ;
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  kgAlloc ;
struct TYPE_10__ {size_t emptyClsPlanGrpId; TYPE_2__* clsPlanGrps; } ;

/* Variables and functions */
 scalar_t__ E_INVALID_STATE ; 
 scalar_t__ E_INVALID_VALUE ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FM_PCD_FREE_KG_CLSPLAN ; 
 int /*<<< orphan*/  FmPcdDecNetEnvOwners (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdSetClsPlanGrpId (TYPE_5__*,int /*<<< orphan*/ ,size_t) ; 
 size_t ILLEGAL_CLS_PLAN ; 
 int /*<<< orphan*/  KgFreeClsPlanEntries (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ XX_IpcSendMessage (int /*<<< orphan*/ ,size_t*,int,size_t*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void FmPcdKgDestroyClsPlanGrp(t_Handle h_FmPcd, uint8_t grpId)
{
    t_FmPcd                         *p_FmPcd = (t_FmPcd*)h_FmPcd;
    t_FmPcdIpcKgClsPlanParams       kgAlloc;
    t_Error                         err;
    t_FmPcdIpcMsg                   msg;
    uint32_t                        replyLength;
    t_FmPcdIpcReply                 reply;

    /* check that no port is bound to this clsPlan */
    if (p_FmPcd->p_FmPcdKg->clsPlanGrps[grpId].owners)
    {
        REPORT_ERROR(MINOR, E_INVALID_STATE, ("Trying to delete a clsPlan grp that has ports bound to"));
        return;
    }

    FmPcdSetClsPlanGrpId(p_FmPcd, p_FmPcd->p_FmPcdKg->clsPlanGrps[grpId].netEnvId, ILLEGAL_CLS_PLAN);

    if (grpId == p_FmPcd->p_FmPcdKg->emptyClsPlanGrpId)
        p_FmPcd->p_FmPcdKg->emptyClsPlanGrpId = ILLEGAL_CLS_PLAN;
    else
        FmPcdDecNetEnvOwners(p_FmPcd, p_FmPcd->p_FmPcdKg->clsPlanGrps[grpId].netEnvId);

    /* free blocks */
    if (p_FmPcd->guestId == NCSW_MASTER_ID)
        KgFreeClsPlanEntries(h_FmPcd,
                             p_FmPcd->p_FmPcdKg->clsPlanGrps[grpId].sizeOfGrp,
                             p_FmPcd->guestId,
                             p_FmPcd->p_FmPcdKg->clsPlanGrps[grpId].baseEntry);
    else    /* in GUEST_PARTITION, we use the IPC, to also set a private driver group if required */
    {
        memset(&reply, 0, sizeof(reply));
        memset(&msg, 0, sizeof(msg));
        kgAlloc.guestId = p_FmPcd->guestId;
        kgAlloc.numOfClsPlanEntries = p_FmPcd->p_FmPcdKg->clsPlanGrps[grpId].sizeOfGrp;
        kgAlloc.clsPlanBase = p_FmPcd->p_FmPcdKg->clsPlanGrps[grpId].baseEntry;
        msg.msgId = FM_PCD_FREE_KG_CLSPLAN;
        memcpy(msg.msgBody, &kgAlloc, sizeof(kgAlloc));
        replyLength = sizeof(uint32_t);
        err = XX_IpcSendMessage(p_FmPcd->h_IpcSession,
                                (uint8_t*)&msg,
                                sizeof(msg.msgId) + sizeof(kgAlloc),
                                (uint8_t*)&reply,
                                &replyLength,
                                NULL,
                                NULL);
        if (err != E_OK)
        {
            REPORT_ERROR(MINOR, err, NO_MSG);
            return;
        }
        if (replyLength != sizeof(uint32_t))
        {
            REPORT_ERROR(MAJOR, E_INVALID_VALUE, ("IPC reply length mismatch"));
            return;
        }
        if ((t_Error)reply.error != E_OK)
        {
            REPORT_ERROR(MAJOR, E_INVALID_STATE, ("Free KG clsPlan failed"));
            return;
        }
    }

    /* clear clsPlan driver structure */
    memset(&p_FmPcd->p_FmPcdKg->clsPlanGrps[grpId], 0, sizeof(t_FmPcdKgClsPlanGrp));
}