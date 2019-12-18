#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_6__ {int savedKeyIndex; int /*<<< orphan*/ * keyAndNextEngineParams; scalar_t__ h_CurrentNode; } ;
typedef  TYPE_1__ t_FmPcdModifyCcKeyAdditionalParams ;
struct TYPE_7__ {int numOfEntries; int /*<<< orphan*/ * keyAndNextEngineParams; } ;
typedef  TYPE_2__ t_FmPcdCcTree ;
struct TYPE_8__ {int numOfKeys; scalar_t__ parseCode; int /*<<< orphan*/ * keyAndNextEngineParams; } ;
typedef  TYPE_3__ t_FmPcdCcNode ;
typedef  int /*<<< orphan*/  t_FmPcdCcKeyAndNextEngineParams ;
typedef  scalar_t__ e_ModifyState ;

/* Variables and functions */
 scalar_t__ CC_PC_FF_IPV4TTL ; 
 scalar_t__ CC_PC_FF_IPV6HOP_LIMIT ; 
 scalar_t__ CC_PC_GENERIC_IC_HASH_INDEXED ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int FALSE ; 
 int FM_PCD_MAX_NUM_OF_CC_GROUPS ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  XX_Free (int /*<<< orphan*/ *) ; 
 scalar_t__ XX_Malloc (int) ; 
 scalar_t__ e_MODIFY_STATE_ADD ; 
 scalar_t__ e_MODIFY_STATE_REMOVE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static t_FmPcdModifyCcKeyAdditionalParams * ModifyNodeCommonPart(
        t_Handle h_FmPcdCcNodeOrTree, uint16_t keyIndex,
        e_ModifyState modifyState, bool ttlCheck, bool hashCheck, bool tree)
{
    t_FmPcdModifyCcKeyAdditionalParams *p_FmPcdModifyCcKeyAdditionalParams;
    int i = 0, j = 0;
    bool wasUpdate = FALSE;
    t_FmPcdCcNode *p_CcNode = NULL;
    t_FmPcdCcTree *p_FmPcdCcTree;
    uint16_t numOfKeys;
    t_FmPcdCcKeyAndNextEngineParams *p_KeyAndNextEngineParams;

    SANITY_CHECK_RETURN_VALUE(h_FmPcdCcNodeOrTree, E_INVALID_HANDLE, NULL);

    if (!tree)
    {
        p_CcNode = (t_FmPcdCcNode *)h_FmPcdCcNodeOrTree;
        numOfKeys = p_CcNode->numOfKeys;

        /* node has to be pointed by another node or tree */

        p_KeyAndNextEngineParams = (t_FmPcdCcKeyAndNextEngineParams *)XX_Malloc(
                sizeof(t_FmPcdCcKeyAndNextEngineParams) * (numOfKeys + 1));
        if (!p_KeyAndNextEngineParams)
        {
            REPORT_ERROR(MAJOR, E_NO_MEMORY, ("Next engine and required action structure"));
            return NULL;
        }
        memcpy(p_KeyAndNextEngineParams, p_CcNode->keyAndNextEngineParams,
               (numOfKeys + 1) * sizeof(t_FmPcdCcKeyAndNextEngineParams));

        if (ttlCheck)
        {
            if ((p_CcNode->parseCode == CC_PC_FF_IPV4TTL)
                    || (p_CcNode->parseCode == CC_PC_FF_IPV6HOP_LIMIT))
            {
                XX_Free(p_KeyAndNextEngineParams);
                REPORT_ERROR(MAJOR, E_INVALID_VALUE, ("nodeId of CC_PC_FF_IPV4TTL or CC_PC_FF_IPV6HOP_LIMIT can not be used for this operation"));
                return NULL;
            }
        }

        if (hashCheck)
        {
            if (p_CcNode->parseCode == CC_PC_GENERIC_IC_HASH_INDEXED)
            {
                XX_Free(p_KeyAndNextEngineParams);
                REPORT_ERROR(MAJOR, E_INVALID_VALUE, ("nodeId of CC_PC_GENERIC_IC_HASH_INDEXED can not be used for this operation"));
                return NULL;
            }
        }
    }
    else
    {
        p_FmPcdCcTree = (t_FmPcdCcTree *)h_FmPcdCcNodeOrTree;
        numOfKeys = p_FmPcdCcTree->numOfEntries;

        p_KeyAndNextEngineParams = (t_FmPcdCcKeyAndNextEngineParams *)XX_Malloc(
                sizeof(t_FmPcdCcKeyAndNextEngineParams)
                        * FM_PCD_MAX_NUM_OF_CC_GROUPS);
        if (!p_KeyAndNextEngineParams)
        {
            REPORT_ERROR(MAJOR, E_NO_MEMORY, ("Next engine and required action structure"));
            return NULL;
        }
        memcpy(p_KeyAndNextEngineParams,
               p_FmPcdCcTree->keyAndNextEngineParams,
               FM_PCD_MAX_NUM_OF_CC_GROUPS
                       * sizeof(t_FmPcdCcKeyAndNextEngineParams));
    }

    p_FmPcdModifyCcKeyAdditionalParams =
            (t_FmPcdModifyCcKeyAdditionalParams *)XX_Malloc(
                    sizeof(t_FmPcdModifyCcKeyAdditionalParams));
    if (!p_FmPcdModifyCcKeyAdditionalParams)
    {
        XX_Free(p_KeyAndNextEngineParams);
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("Allocation of internal data structure FAILED"));
        return NULL;
    }
    memset(p_FmPcdModifyCcKeyAdditionalParams, 0,
           sizeof(t_FmPcdModifyCcKeyAdditionalParams));

    p_FmPcdModifyCcKeyAdditionalParams->h_CurrentNode = h_FmPcdCcNodeOrTree;
    p_FmPcdModifyCcKeyAdditionalParams->savedKeyIndex = keyIndex;

    while (i < numOfKeys)
    {
        if ((j == keyIndex) && !wasUpdate)
        {
            if (modifyState == e_MODIFY_STATE_ADD)
                j++;
            else
                if (modifyState == e_MODIFY_STATE_REMOVE)
                    i++;
            wasUpdate = TRUE;
        }
        else
        {
            memcpy(&p_FmPcdModifyCcKeyAdditionalParams->keyAndNextEngineParams[j],
                   p_KeyAndNextEngineParams + i,
                   sizeof(t_FmPcdCcKeyAndNextEngineParams));
            i++;
            j++;
        }
    }

    if (keyIndex == numOfKeys)
    {
        if (modifyState == e_MODIFY_STATE_ADD)
            j++;
    }

    memcpy(&p_FmPcdModifyCcKeyAdditionalParams->keyAndNextEngineParams[j],
           p_KeyAndNextEngineParams + numOfKeys,
           sizeof(t_FmPcdCcKeyAndNextEngineParams));

    XX_Free(p_KeyAndNextEngineParams);

    return p_FmPcdModifyCcKeyAdditionalParams;
}