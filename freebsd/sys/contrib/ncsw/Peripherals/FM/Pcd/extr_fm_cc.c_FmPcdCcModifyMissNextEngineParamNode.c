#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  t_List ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_FmPcdModifyCcKeyAdditionalParams ;
struct TYPE_7__ {scalar_t__ maxNumOfKeys; scalar_t__ h_FmPcd; int /*<<< orphan*/  numOfKeys; } ;
typedef  TYPE_1__ t_FmPcdCcNode ;
typedef  int /*<<< orphan*/  t_FmPcdCcNextEngineParams ;
struct TYPE_8__ {int /*<<< orphan*/  shadowLock; int /*<<< orphan*/  h_ShadowSpinlock; } ;
typedef  TYPE_2__ t_FmPcd ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 scalar_t__ BuildNewNodeModifyNextEngine (scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ DoDynamicChange (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_BUSY ; 
 scalar_t__ E_INVALID_STATE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INIT_LIST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/ * ModifyNodeCommonPart (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TRY_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XX_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_MODIFY_STATE_CHANGE ; 

t_Error FmPcdCcModifyMissNextEngineParamNode(
        t_Handle h_FmPcd, t_Handle h_FmPcdCcNode,
        t_FmPcdCcNextEngineParams *p_FmPcdCcNextEngineParams)
{
    t_FmPcdCcNode *p_CcNode = (t_FmPcdCcNode *)h_FmPcdCcNode;
    t_FmPcd *p_FmPcd;
    t_List h_OldPointersLst, h_NewPointersLst;
    uint16_t keyIndex;
    t_FmPcdModifyCcKeyAdditionalParams *p_ModifyKeyParams;
    t_Error err = E_OK;

    SANITY_CHECK_RETURN_ERROR(p_CcNode, E_INVALID_VALUE);

    keyIndex = p_CcNode->numOfKeys;

    p_FmPcd = (t_FmPcd *)p_CcNode->h_FmPcd;

    INIT_LIST(&h_OldPointersLst);
    INIT_LIST(&h_NewPointersLst);

    p_ModifyKeyParams = ModifyNodeCommonPart(p_CcNode, keyIndex,
                                             e_MODIFY_STATE_CHANGE, FALSE, TRUE,
                                             FALSE);
    if (!p_ModifyKeyParams)
        RETURN_ERROR(MAJOR, E_INVALID_STATE, NO_MSG);

    if (p_CcNode->maxNumOfKeys
            && !TRY_LOCK(p_FmPcd->h_ShadowSpinlock, &p_FmPcd->shadowLock))
    {
        XX_Free(p_ModifyKeyParams);
        return ERROR_CODE(E_BUSY);
    }

    err = BuildNewNodeModifyNextEngine(h_FmPcd, p_CcNode, keyIndex,
                                       p_FmPcdCcNextEngineParams,
                                       &h_OldPointersLst, &h_NewPointersLst,
                                       p_ModifyKeyParams);
    if (err)
    {
        XX_Free(p_ModifyKeyParams);
        if (p_CcNode->maxNumOfKeys)
            RELEASE_LOCK(p_FmPcd->shadowLock);
        RETURN_ERROR(MAJOR, err, NO_MSG);
    }

    err = DoDynamicChange(p_FmPcd, &h_OldPointersLst, &h_NewPointersLst,
                          p_ModifyKeyParams, FALSE);

    if (p_CcNode->maxNumOfKeys)
        RELEASE_LOCK(p_FmPcd->shadowLock);

    return err;
}