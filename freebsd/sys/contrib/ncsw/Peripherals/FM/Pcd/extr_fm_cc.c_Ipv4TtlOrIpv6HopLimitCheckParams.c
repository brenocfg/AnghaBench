#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  t_Handle ;
struct TYPE_24__ {scalar_t__ h_Manip; } ;
struct TYPE_16__ {int maxNumOfKeys; TYPE_7__* keyParams; TYPE_9__ ccNextEngineParamsForMiss; int /*<<< orphan*/  statisticsMode; } ;
struct TYPE_20__ {TYPE_1__ keysParams; } ;
typedef  TYPE_5__ t_FmPcdCcNodeParams ;
struct TYPE_21__ {int numOfKeys; TYPE_4__* keyAndNextEngineParams; int /*<<< orphan*/  statisticsMode; int /*<<< orphan*/  countersArraySize; int /*<<< orphan*/  numOfStatsFLRs; } ;
typedef  TYPE_6__ t_FmPcdCcNode ;
typedef  int /*<<< orphan*/  t_FmPcdCcNextEngineParams ;
struct TYPE_22__ {TYPE_9__ ccNextEngineParams; int /*<<< orphan*/  p_Key; scalar_t__ p_Mask; } ;
typedef  TYPE_7__ t_FmPcdCcKeyParams ;
typedef  scalar_t__ t_Error ;
struct TYPE_17__ {int /*<<< orphan*/  h_CcNode; } ;
struct TYPE_18__ {TYPE_2__ ccParams; } ;
struct TYPE_23__ {scalar_t__ nextEngine; TYPE_3__ params; scalar_t__ h_Manip; } ;
struct TYPE_19__ {int* key; int* mask; void* requiredAction; TYPE_8__ nextEngineParams; } ;

/* Variables and functions */
 scalar_t__ AllocAndFillAdForContLookupManip (int /*<<< orphan*/ ) ; 
 scalar_t__ E_INVALID_VALUE ; 
 scalar_t__ E_OK ; 
 int FALSE ; 
 scalar_t__ FmPcdManipCheckParamsForCcNextEngine (TYPE_9__*,void**) ; 
 int /*<<< orphan*/  MAJOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ ValidateAndCalcStatsParams (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ValidateNextEngineParams (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ) ; 
 scalar_t__ e_FM_PCD_CC ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_8__*,TYPE_9__*,int) ; 

__attribute__((used)) static t_Error Ipv4TtlOrIpv6HopLimitCheckParams(
        t_Handle h_FmPcd, t_FmPcdCcNodeParams *p_CcNodeParam,
        t_FmPcdCcNode *p_CcNode, bool *isKeyTblAlloc)
{
    int tmp = 0;
    t_FmPcdCcKeyParams *p_KeyParams;
    t_Error err;
    uint8_t key = 0x01;
    uint32_t requiredAction = 0;

    if (p_CcNode->numOfKeys != 1)
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("For node of the type IPV4_TTL or IPV6_HOP_LIMIT the maximal supported 'numOfKeys' is 1"));

    if ((p_CcNodeParam->keysParams.maxNumOfKeys)
            && (p_CcNodeParam->keysParams.maxNumOfKeys != 1))
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("For node of the type IPV4_TTL or IPV6_HOP_LIMIT the maximal supported 'maxNumOfKeys' is 1"));

    /* Validate statistics parameters */
    err = ValidateAndCalcStatsParams(p_CcNode, p_CcNodeParam,
                                     &(p_CcNode->numOfStatsFLRs),
                                     &(p_CcNode->countersArraySize));
    if (err)
        RETURN_ERROR(MAJOR, err, ("Invalid statistics parameters"));

    err = ValidateNextEngineParams(
            h_FmPcd, &p_CcNodeParam->keysParams.ccNextEngineParamsForMiss,
            p_CcNodeParam->keysParams.statisticsMode);
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

        if (p_KeyParams->p_Mask)
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("For node of the type IPV4_TTL or IPV6_HOP_LIMIT p_Mask can not be initialized"));

        if (memcmp(p_KeyParams->p_Key, &key, 1) != 0)
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("For node of the type IPV4_TTL or IPV6_HOP_LIMIT p_Key has to be 1"));

        err = ValidateNextEngineParams(h_FmPcd,
                                       &p_KeyParams->ccNextEngineParams,
                                       p_CcNode->statisticsMode);
        if (err)
            RETURN_ERROR(MAJOR, err, (NO_MSG));

        if (p_KeyParams->ccNextEngineParams.h_Manip)
        {
            err = FmPcdManipCheckParamsForCcNextEngine(
                    &p_KeyParams->ccNextEngineParams, &requiredAction);
            if (err)
                RETURN_ERROR(MAJOR, err, (NO_MSG));
        }

        /* Store 'key' parameters - key (fixed to 0x01), key size of 1 byte and full mask */
        p_CcNode->keyAndNextEngineParams[tmp].key[0] = key;
        p_CcNode->keyAndNextEngineParams[tmp].mask[0] = 0xFF;

        /* Store NextEngine parameters */
        memcpy(&p_CcNode->keyAndNextEngineParams[tmp].nextEngineParams,
               &p_KeyParams->ccNextEngineParams,
               sizeof(t_FmPcdCcNextEngineParams));

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
        p_CcNode->keyAndNextEngineParams[tmp].requiredAction = requiredAction;
    }

    *isKeyTblAlloc = FALSE;

    return E_OK;
}