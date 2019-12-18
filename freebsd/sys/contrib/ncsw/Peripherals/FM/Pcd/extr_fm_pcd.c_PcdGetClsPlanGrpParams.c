#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_14__ {size_t netEnvId; scalar_t__ clsPlanGrpId; int numOfOptions; scalar_t__* options; void* grpExists; int /*<<< orphan*/ * optVectors; } ;
typedef  TYPE_5__ t_FmPcdKgInterModuleClsPlanGrpParams ;
struct TYPE_15__ {TYPE_4__* p_FmPcdKg; TYPE_3__* netEnvs; } ;
typedef  TYPE_6__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_13__ {scalar_t__ emptyClsPlanGrpId; } ;
struct TYPE_12__ {scalar_t__ clsPlanGrpId; TYPE_2__* units; int /*<<< orphan*/ * unitsVectors; } ;
struct TYPE_11__ {TYPE_1__* hdrs; } ;
struct TYPE_10__ {scalar_t__ hdr; scalar_t__ opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_6__*) ; 
 int /*<<< orphan*/  E_OK ; 
 int FM_PCD_MAX_NUM_OF_DISTINCTION_UNITS ; 
 int FM_PCD_MAX_NUM_OF_INTERCHANGEABLE_HDRS ; 
 scalar_t__ HEADER_TYPE_NONE ; 
 scalar_t__ ILLEGAL_CLS_PLAN ; 
 void* TRUE ; 

t_Error PcdGetClsPlanGrpParams(t_FmPcd *p_FmPcd, t_FmPcdKgInterModuleClsPlanGrpParams *p_GrpParams)
{
    uint8_t netEnvId = p_GrpParams->netEnvId;
    int     i, k, j;

    ASSERT_COND(p_FmPcd);
    if (p_FmPcd->netEnvs[netEnvId].clsPlanGrpId != ILLEGAL_CLS_PLAN)
    {
        p_GrpParams->grpExists = TRUE;
        p_GrpParams->clsPlanGrpId = p_FmPcd->netEnvs[netEnvId].clsPlanGrpId;
        return E_OK;
    }

    for (i=0; ((i < FM_PCD_MAX_NUM_OF_DISTINCTION_UNITS) &&
              (p_FmPcd->netEnvs[netEnvId].units[i].hdrs[0].hdr != HEADER_TYPE_NONE)); i++)
    {
        for (k=0; ((k < FM_PCD_MAX_NUM_OF_INTERCHANGEABLE_HDRS) &&
                   (p_FmPcd->netEnvs[netEnvId].units[i].hdrs[k].hdr != HEADER_TYPE_NONE)); k++)
        {
            /* if an option exists, add it to the opts list */
            if (p_FmPcd->netEnvs[netEnvId].units[i].hdrs[k].opt)
            {
                /* check if this option already exists, add if it doesn't */
                for (j = 0;j<p_GrpParams->numOfOptions;j++)
                {
                    if (p_GrpParams->options[j] == p_FmPcd->netEnvs[netEnvId].units[i].hdrs[k].opt)
                        break;
                }
                p_GrpParams->optVectors[j] |= p_FmPcd->netEnvs[netEnvId].unitsVectors[i];
                if (j == p_GrpParams->numOfOptions)
                {
                    p_GrpParams->options[p_GrpParams->numOfOptions] = p_FmPcd->netEnvs[netEnvId].units[i].hdrs[k].opt;
                    p_GrpParams->numOfOptions++;
                }
            }
        }
    }

    if (p_GrpParams->numOfOptions == 0)
    {
        if (p_FmPcd->p_FmPcdKg->emptyClsPlanGrpId != ILLEGAL_CLS_PLAN)
        {
            p_GrpParams->grpExists = TRUE;
            p_GrpParams->clsPlanGrpId = p_FmPcd->p_FmPcdKg->emptyClsPlanGrpId;
        }
    }

    return E_OK;

}