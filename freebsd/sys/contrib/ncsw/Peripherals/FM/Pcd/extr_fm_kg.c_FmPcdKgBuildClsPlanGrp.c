#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_16__ {int numOfClsPlanEntries; int* vectors; void* baseEntry; } ;
typedef  TYPE_2__ t_FmPcdKgInterModuleClsPlanSet ;
struct TYPE_17__ {int numOfOptions; int* optVectors; int /*<<< orphan*/ * options; int /*<<< orphan*/  netEnvId; void* clsPlanGrpId; } ;
typedef  TYPE_3__ t_FmPcdKgInterModuleClsPlanGrpParams ;
struct TYPE_18__ {int sizeOfGrp; int /*<<< orphan*/ * optArray; void* baseEntry; scalar_t__ owners; int /*<<< orphan*/  netEnvId; scalar_t__ used; } ;
typedef  TYPE_4__ t_FmPcdKgClsPlanGrp ;
struct TYPE_19__ {scalar_t__ guestId; int numOfClsPlanEntries; scalar_t__ replyBody; scalar_t__ error; int /*<<< orphan*/  msgBody; int /*<<< orphan*/  msgId; } ;
typedef  TYPE_5__ t_FmPcdIpcReply ;
typedef  TYPE_5__ t_FmPcdIpcMsg ;
typedef  TYPE_5__ t_FmPcdIpcKgClsPlanParams ;
struct TYPE_20__ {scalar_t__ guestId; int /*<<< orphan*/  h_IpcSession; TYPE_1__* p_FmPcdKg; } ;
typedef  TYPE_8__ t_FmPcd ;
typedef  scalar_t__ t_Error ;
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  kgAlloc ;
struct TYPE_15__ {TYPE_4__* clsPlanGrps; void* emptyClsPlanGrpId; } ;

/* Variables and functions */
 int CLS_PLAN_NUM_PER_GRP ; 
 scalar_t__ E_FULL ; 
 scalar_t__ E_INVALID_STATE ; 
 scalar_t__ E_INVALID_VALUE ; 
 scalar_t__ E_OK ; 
 int FM_MAX_NUM_OF_PORTS ; 
 int /*<<< orphan*/  FM_PCD_ALLOC_KG_CLSPLAN ; 
 int /*<<< orphan*/  FM_PCD_MAX_NUM_OF_CLS_PLANS ; 
 int FM_PCD_MAX_NUM_OF_OPTIONS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdIncNetEnvOwners (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdSetClsPlanGrpId (TYPE_8__*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ KgAllocClsPlanEntries (scalar_t__,int,scalar_t__,void**) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ TRUE ; 
 scalar_t__ XX_IpcSendMessage (int /*<<< orphan*/ ,void**,int,void**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

t_Error FmPcdKgBuildClsPlanGrp(t_Handle h_FmPcd, t_FmPcdKgInterModuleClsPlanGrpParams *p_Grp, t_FmPcdKgInterModuleClsPlanSet *p_ClsPlanSet)
{
    t_FmPcd                         *p_FmPcd = (t_FmPcd*)h_FmPcd;
    t_FmPcdKgClsPlanGrp             *p_ClsPlanGrp;
    t_FmPcdIpcKgClsPlanParams       kgAlloc;
    t_Error                         err = E_OK;
    uint32_t                        oredVectors = 0;
    int                             i, j;

    /* this routine is protected by the calling routine ! */
    if (p_Grp->numOfOptions >= FM_PCD_MAX_NUM_OF_OPTIONS(FM_PCD_MAX_NUM_OF_CLS_PLANS))
        RETURN_ERROR(MAJOR, E_INVALID_VALUE,("Too many classification plan basic options selected."));

    /* find a new clsPlan group */
    for (i = 0; i < FM_MAX_NUM_OF_PORTS; i++)
        if (!p_FmPcd->p_FmPcdKg->clsPlanGrps[i].used)
            break;
    if (i == FM_MAX_NUM_OF_PORTS)
        RETURN_ERROR(MAJOR, E_FULL,("No classification plan groups available."));

    p_FmPcd->p_FmPcdKg->clsPlanGrps[i].used = TRUE;

    p_Grp->clsPlanGrpId = (uint8_t)i;

    if (p_Grp->numOfOptions == 0)
        p_FmPcd->p_FmPcdKg->emptyClsPlanGrpId = (uint8_t)i;

    p_ClsPlanGrp = &p_FmPcd->p_FmPcdKg->clsPlanGrps[i];
    p_ClsPlanGrp->netEnvId = p_Grp->netEnvId;
    p_ClsPlanGrp->owners = 0;
    FmPcdSetClsPlanGrpId(p_FmPcd, p_Grp->netEnvId, p_Grp->clsPlanGrpId);
    if (p_Grp->numOfOptions != 0)
        FmPcdIncNetEnvOwners(p_FmPcd, p_Grp->netEnvId);

    p_ClsPlanGrp->sizeOfGrp = (uint16_t)(1 << p_Grp->numOfOptions);
    /* a minimal group of 8 is required */
    if (p_ClsPlanGrp->sizeOfGrp < CLS_PLAN_NUM_PER_GRP)
        p_ClsPlanGrp->sizeOfGrp = CLS_PLAN_NUM_PER_GRP;
    if (p_FmPcd->guestId == NCSW_MASTER_ID)
    {
        err = KgAllocClsPlanEntries(h_FmPcd, p_ClsPlanGrp->sizeOfGrp, p_FmPcd->guestId, &p_ClsPlanGrp->baseEntry);

        if (err)
            RETURN_ERROR(MINOR, E_INVALID_STATE, NO_MSG);
    }
    else
    {
        t_FmPcdIpcMsg   msg;
        uint32_t        replyLength;
        t_FmPcdIpcReply reply;

        /* in GUEST_PARTITION, we use the IPC, to also set a private driver group if required */
        memset(&reply, 0, sizeof(reply));
        memset(&msg, 0, sizeof(msg));
        memset(&kgAlloc, 0, sizeof(kgAlloc));
        kgAlloc.guestId = p_FmPcd->guestId;
        kgAlloc.numOfClsPlanEntries = p_ClsPlanGrp->sizeOfGrp;
        msg.msgId = FM_PCD_ALLOC_KG_CLSPLAN;
        memcpy(msg.msgBody, &kgAlloc, sizeof(kgAlloc));
        replyLength = (sizeof(uint32_t) + sizeof(p_ClsPlanGrp->baseEntry));
        if ((err = XX_IpcSendMessage(p_FmPcd->h_IpcSession,
                                     (uint8_t*)&msg,
                                     sizeof(msg.msgId) + sizeof(kgAlloc),
                                     (uint8_t*)&reply,
                                     &replyLength,
                                     NULL,
                                     NULL)) != E_OK)
            RETURN_ERROR(MAJOR, err, NO_MSG);

        if (replyLength != (sizeof(uint32_t) + sizeof(p_ClsPlanGrp->baseEntry)))
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("IPC reply length mismatch"));
        if ((t_Error)reply.error != E_OK)
            RETURN_ERROR(MINOR, (t_Error)reply.error, NO_MSG);

        p_ClsPlanGrp->baseEntry = *(uint8_t*)(reply.replyBody);
    }

    /* build classification plan entries parameters */
    p_ClsPlanSet->baseEntry = p_ClsPlanGrp->baseEntry;
    p_ClsPlanSet->numOfClsPlanEntries = p_ClsPlanGrp->sizeOfGrp;

    oredVectors = 0;
    for (i = 0; i<p_Grp->numOfOptions; i++)
    {
        oredVectors |= p_Grp->optVectors[i];
        /* save an array of used options - the indexes represent the power of 2 index */
        p_ClsPlanGrp->optArray[i] = p_Grp->options[i];
    }
    /* set the classification plan relevant entries so that all bits
     * relevant to the list of options is cleared
     */
    for (j = 0; j<p_ClsPlanGrp->sizeOfGrp; j++)
        p_ClsPlanSet->vectors[j] = ~oredVectors;

    for (i = 0; i<p_Grp->numOfOptions; i++)
    {
       /* option i got the place 2^i in the clsPlan array. all entries that
         * have bit i set, should have the vector bit cleared. So each option
         * has one location that it is exclusive (1,2,4,8...) and represent the
         * presence of that option only, and other locations that represent a
         * combination of options.
         * e.g:
         * If ethernet-BC is option 1 it gets entry 2 in the table. Entry 2
         * now represents a frame with ethernet-BC header - so the bit
         * representing ethernet-BC should be set and all other option bits
         * should be cleared.
         * Entries 2,3,6,7,10... also have ethernet-BC and therefore have bit
         * vector[1] set, but they also have other bits set:
         * 3=1+2, options 0 and 1
         * 6=2+4, options 1 and 2
         * 7=1+2+4, options 0,1,and 2
         * 10=2+8, options 1 and 3
         * etc.
         * */

        /* now for each option (i), we set their bits in all entries (j)
         * that contain bit 2^i.
         */
        for (j = 0; j<p_ClsPlanGrp->sizeOfGrp; j++)
        {
            if (j & (1<<i))
                p_ClsPlanSet->vectors[j] |= p_Grp->optVectors[i];
        }
    }

    return E_OK;
}