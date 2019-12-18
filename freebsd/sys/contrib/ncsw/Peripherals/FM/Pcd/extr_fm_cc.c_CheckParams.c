#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  t_Handle ;
struct TYPE_26__ {scalar_t__ h_Manip; } ;
struct TYPE_18__ {int keySize; TYPE_7__* keyParams; TYPE_9__ ccNextEngineParamsForMiss; } ;
struct TYPE_22__ {TYPE_1__ keysParams; } ;
typedef  TYPE_5__ t_FmPcdCcNodeParams ;
struct TYPE_23__ {size_t numOfKeys; int maxNumOfKeys; TYPE_4__* keyAndNextEngineParams; int /*<<< orphan*/  statisticsMode; int /*<<< orphan*/  countersArraySize; int /*<<< orphan*/  numOfStatsFLRs; } ;
typedef  TYPE_6__ t_FmPcdCcNode ;
typedef  int /*<<< orphan*/  t_FmPcdCcNextEngineParams ;
struct TYPE_24__ {TYPE_9__ ccNextEngineParams; TYPE_9__* p_Mask; TYPE_9__* p_Key; } ;
typedef  TYPE_7__ t_FmPcdCcKeyParams ;
typedef  scalar_t__ t_Error ;
struct TYPE_19__ {int /*<<< orphan*/  h_CcNode; } ;
struct TYPE_20__ {TYPE_2__ ccParams; } ;
struct TYPE_25__ {scalar_t__ nextEngine; TYPE_3__ params; scalar_t__ h_Manip; } ;
struct TYPE_21__ {TYPE_8__ nextEngineParams; void* requiredAction; TYPE_8__* mask; TYPE_8__* key; } ;

/* Variables and functions */
 scalar_t__ AllocAndFillAdForContLookupManip (int /*<<< orphan*/ ) ; 
 scalar_t__ E_INVALID_VALUE ; 
 scalar_t__ E_OK ; 
 scalar_t__ FmPcdManipCheckParamsForCcNextEngine (TYPE_9__*,void**) ; 
 int /*<<< orphan*/  MAJOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int TRUE ; 
 scalar_t__ UpdateGblMask (TYPE_6__*,int,TYPE_9__*) ; 
 scalar_t__ ValidateAndCalcStatsParams (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ValidateNextEngineParams (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ) ; 
 scalar_t__ e_FM_PCD_CC ; 
 int /*<<< orphan*/  memcpy (TYPE_8__*,TYPE_9__*,int) ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 

__attribute__((used)) static t_Error CheckParams(t_Handle h_FmPcd, t_FmPcdCcNodeParams *p_CcNodeParam,
                           t_FmPcdCcNode *p_CcNode, bool *isKeyTblAlloc)
{
    int tmp = 0;
    t_FmPcdCcKeyParams *p_KeyParams;
    t_Error err;
    uint32_t requiredAction = 0;

    /* Validate statistics parameters */
    err = ValidateAndCalcStatsParams(p_CcNode, p_CcNodeParam,
                                     &(p_CcNode->numOfStatsFLRs),
                                     &(p_CcNode->countersArraySize));
    if (err)
        RETURN_ERROR(MAJOR, err, ("Invalid statistics parameters"));

    /* Validate next engine parameters on Miss */
    err = ValidateNextEngineParams(
            h_FmPcd, &p_CcNodeParam->keysParams.ccNextEngineParamsForMiss,
            p_CcNode->statisticsMode);
    if (err)
        RETURN_ERROR(MAJOR, err,
                     ("For this node MissNextEngineParams are not valid"));

    if (p_CcNodeParam->keysParams.ccNextEngineParamsForMiss.h_Manip)
    {
        err = FmPcdManipCheckParamsForCcNextEngine(
                &p_CcNodeParam->keysParams.ccNextEngineParamsForMiss,
                &requiredAction);
        if (err)
            RETURN_ERROR(MAJOR, err, (NO_MSG));
    }

    memcpy(&p_CcNode->keyAndNextEngineParams[p_CcNode->numOfKeys].nextEngineParams,
           &p_CcNodeParam->keysParams.ccNextEngineParamsForMiss,
           sizeof(t_FmPcdCcNextEngineParams));

    p_CcNode->keyAndNextEngineParams[p_CcNode->numOfKeys].requiredAction =
            requiredAction;

    if ((p_CcNode->keyAndNextEngineParams[p_CcNode->numOfKeys].nextEngineParams.nextEngine
            == e_FM_PCD_CC)
            && p_CcNode->keyAndNextEngineParams[p_CcNode->numOfKeys].nextEngineParams.h_Manip)
    {
        err =
                AllocAndFillAdForContLookupManip(
                        p_CcNode->keyAndNextEngineParams[p_CcNode->numOfKeys].nextEngineParams.params.ccParams.h_CcNode);
        if (err)
            RETURN_ERROR(MAJOR, err, (NO_MSG));
    }

    for (tmp = 0; tmp < p_CcNode->numOfKeys; tmp++)
    {
        p_KeyParams = &p_CcNodeParam->keysParams.keyParams[tmp];

        if (!p_KeyParams->p_Key)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("p_Key is not initialized"));

        err = ValidateNextEngineParams(h_FmPcd,
                                       &p_KeyParams->ccNextEngineParams,
                                       p_CcNode->statisticsMode);
        if (err)
            RETURN_ERROR(MAJOR, err, (NO_MSG));

        err = UpdateGblMask(p_CcNode, p_CcNodeParam->keysParams.keySize,
                            p_KeyParams->p_Mask);
        if (err)
            RETURN_ERROR(MAJOR, err, (NO_MSG));

        if (p_KeyParams->ccNextEngineParams.h_Manip)
        {
            err = FmPcdManipCheckParamsForCcNextEngine(
                    &p_KeyParams->ccNextEngineParams, &requiredAction);
            if (err)
                RETURN_ERROR(MAJOR, err, (NO_MSG));
        }

        /* Store 'key' parameters - key, mask (if passed by the user) */
        memcpy(p_CcNode->keyAndNextEngineParams[tmp].key, p_KeyParams->p_Key,
               p_CcNodeParam->keysParams.keySize);

        if (p_KeyParams->p_Mask)
            memcpy(p_CcNode->keyAndNextEngineParams[tmp].mask,
                   p_KeyParams->p_Mask, p_CcNodeParam->keysParams.keySize);
        else
            memset((void *)(p_CcNode->keyAndNextEngineParams[tmp].mask), 0xFF,
                   p_CcNodeParam->keysParams.keySize);

        /* Store next engine parameters */
        memcpy(&p_CcNode->keyAndNextEngineParams[tmp].nextEngineParams,
               &p_KeyParams->ccNextEngineParams,
               sizeof(t_FmPcdCcNextEngineParams));

        p_CcNode->keyAndNextEngineParams[tmp].requiredAction = requiredAction;

        if ((p_CcNode->keyAndNextEngineParams[tmp].nextEngineParams.nextEngine
                == e_FM_PCD_CC)
                && p_CcNode->keyAndNextEngineParams[tmp].nextEngineParams.h_Manip)
        {
            err =
                    AllocAndFillAdForContLookupManip(
                            p_CcNode->keyAndNextEngineParams[tmp].nextEngineParams.params.ccParams.h_CcNode);
            if (err)
                RETURN_ERROR(MAJOR, err, (NO_MSG));
        }
    }

    if (p_CcNode->maxNumOfKeys)
    {
        if (p_CcNode->maxNumOfKeys < p_CcNode->numOfKeys)
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("Number of keys exceed the provided maximal number of keys"));
    }

    *isKeyTblAlloc = TRUE;

    return E_OK;
}