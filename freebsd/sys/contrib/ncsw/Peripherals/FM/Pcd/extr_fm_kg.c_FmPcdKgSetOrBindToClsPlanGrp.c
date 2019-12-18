#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_16__ {size_t clsPlanGrpId; size_t netEnvId; scalar_t__ grpExists; } ;
typedef  TYPE_2__ t_FmPcdKgInterModuleClsPlanSet ;
typedef  TYPE_2__ t_FmPcdKgInterModuleClsPlanGrpParams ;
struct TYPE_17__ {int /*<<< orphan*/  optArray; int /*<<< orphan*/  owners; } ;
typedef  TYPE_4__ t_FmPcdKgClsPlanGrp ;
struct TYPE_18__ {TYPE_1__* p_FmPcdKg; scalar_t__ h_Hc; } ;
typedef  TYPE_5__ t_FmPcd ;
typedef  scalar_t__ t_Error ;
typedef  int /*<<< orphan*/  protocolOpt_t ;
typedef  int /*<<< orphan*/  grpParams ;
struct TYPE_15__ {size_t emptyClsPlanGrpId; TYPE_4__* clsPlanGrps; } ;

/* Variables and functions */
 scalar_t__ BindPortToClsPlanGrp (TYPE_5__*,size_t,size_t) ; 
 scalar_t__ E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 int FALSE ; 
 int /*<<< orphan*/  FM_PCD_MAX_NUM_OF_CLS_PLANS ; 
 int FM_PCD_MAX_NUM_OF_OPTIONS (int /*<<< orphan*/ ) ; 
 scalar_t__ FmHcPcdKgSetClsPlan (scalar_t__,TYPE_2__*) ; 
 scalar_t__ FmPcdKgBuildClsPlanGrp (scalar_t__,TYPE_2__*,TYPE_2__*) ; 
 size_t ILLEGAL_CLS_PLAN ; 
 int /*<<< orphan*/  KgSetClsPlan (TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 char* NO_MSG ; 
 scalar_t__ PcdGetClsPlanGrpParams (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  XX_Free (TYPE_2__*) ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

t_Error FmPcdKgSetOrBindToClsPlanGrp(t_Handle h_FmPcd, uint8_t hardwarePortId, uint8_t netEnvId, protocolOpt_t *p_OptArray, uint8_t *p_ClsPlanGrpId, bool *p_IsEmptyClsPlanGrp)
{
    t_FmPcd                                 *p_FmPcd = (t_FmPcd *)h_FmPcd;
    t_FmPcdKgInterModuleClsPlanGrpParams    grpParams, *p_GrpParams;
    t_FmPcdKgClsPlanGrp                     *p_ClsPlanGrp;
    t_FmPcdKgInterModuleClsPlanSet          *p_ClsPlanSet;
    t_Error                                 err;

    /* This function is issued only from FM_PORT_SetPcd which locked all PCD modules,
       so no need for lock here */

    memset(&grpParams, 0, sizeof(grpParams));
    grpParams.clsPlanGrpId = ILLEGAL_CLS_PLAN;
    p_GrpParams = &grpParams;

    p_GrpParams->netEnvId = netEnvId;

    /* Get from the NetEnv the information of the clsPlan (can be already created,
     * or needs to build) */
    err = PcdGetClsPlanGrpParams(h_FmPcd, p_GrpParams);
    if (err)
        RETURN_ERROR(MINOR,err,NO_MSG);

    if (p_GrpParams->grpExists)
    {
        /* this group was already updated (at least) in SW */
        *p_ClsPlanGrpId = p_GrpParams->clsPlanGrpId;
    }
    else
    {
        p_ClsPlanSet = (t_FmPcdKgInterModuleClsPlanSet *)XX_Malloc(sizeof(t_FmPcdKgInterModuleClsPlanSet));
        if (!p_ClsPlanSet)
            RETURN_ERROR(MAJOR, E_NO_MEMORY, ("Classification plan set"));
        memset(p_ClsPlanSet, 0, sizeof(t_FmPcdKgInterModuleClsPlanSet));
        /* Build (in SW) the clsPlan parameters, including the vectors to be written to HW */
        err = FmPcdKgBuildClsPlanGrp(h_FmPcd, p_GrpParams, p_ClsPlanSet);
        if (err)
        {
            XX_Free(p_ClsPlanSet);
            RETURN_ERROR(MINOR, err, NO_MSG);
        }
        *p_ClsPlanGrpId = p_GrpParams->clsPlanGrpId;

        if (p_FmPcd->h_Hc)
        {
            /* write clsPlan entries to memory */
            err = FmHcPcdKgSetClsPlan(p_FmPcd->h_Hc, p_ClsPlanSet);
            if (err)
            {
                XX_Free(p_ClsPlanSet);
                RETURN_ERROR(MAJOR, err, NO_MSG);
            }
        }
        else
            /* write clsPlan entries to memory */
            KgSetClsPlan(p_FmPcd, p_ClsPlanSet);

        XX_Free(p_ClsPlanSet);
    }

    /* Set caller parameters     */

    /* mark if this is an empty classification group */
    if (*p_ClsPlanGrpId == p_FmPcd->p_FmPcdKg->emptyClsPlanGrpId)
        *p_IsEmptyClsPlanGrp = TRUE;
    else
        *p_IsEmptyClsPlanGrp = FALSE;

    p_ClsPlanGrp = &p_FmPcd->p_FmPcdKg->clsPlanGrps[*p_ClsPlanGrpId];

   /* increment owners number */
    p_ClsPlanGrp->owners++;

    /* copy options array for port */
    memcpy(p_OptArray, &p_FmPcd->p_FmPcdKg->clsPlanGrps[*p_ClsPlanGrpId].optArray, FM_PCD_MAX_NUM_OF_OPTIONS(FM_PCD_MAX_NUM_OF_CLS_PLANS)*sizeof(protocolOpt_t));

    /* bind port to the new or existing group */
    err = BindPortToClsPlanGrp(p_FmPcd, hardwarePortId, p_GrpParams->clsPlanGrpId);
    if (err)
        RETURN_ERROR(MINOR, err, NO_MSG);

    return E_OK;
}