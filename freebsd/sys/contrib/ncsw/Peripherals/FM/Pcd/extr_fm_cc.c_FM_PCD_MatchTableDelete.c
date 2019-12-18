#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_14__ {int numOfKeys; TYPE_5__* keyAndNextEngineParams; scalar_t__ owners; struct TYPE_14__* h_FmPcd; } ;
typedef  TYPE_6__ t_FmPcdCcNode ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_10__ {scalar_t__ h_FrmReplic; } ;
struct TYPE_9__ {int /*<<< orphan*/  h_CcNode; } ;
struct TYPE_11__ {TYPE_2__ frParams; TYPE_1__ ccParams; } ;
struct TYPE_12__ {scalar_t__ nextEngine; TYPE_3__ params; scalar_t__ h_Manip; } ;
struct TYPE_13__ {TYPE_4__ nextEngineParams; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteNode (TYPE_6__*) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FmPcdManipUpdateOwner (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FrmReplicGroupUpdateOwner (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateNodeOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e_FM_PCD_CC ; 
 scalar_t__ e_FM_PCD_FR ; 

t_Error FM_PCD_MatchTableDelete(t_Handle h_CcNode)
{
    t_FmPcdCcNode *p_CcNode = (t_FmPcdCcNode *)h_CcNode;
    int i = 0;

    SANITY_CHECK_RETURN_ERROR(p_CcNode, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_CcNode->h_FmPcd, E_INVALID_HANDLE);

    if (p_CcNode->owners)
        RETURN_ERROR(
                MAJOR,
                E_INVALID_STATE,
                ("This node cannot be removed because it is occupied; first unbind this node"));

    for (i = 0; i < p_CcNode->numOfKeys; i++)
        if (p_CcNode->keyAndNextEngineParams[i].nextEngineParams.nextEngine
                == e_FM_PCD_CC)
            UpdateNodeOwner(
                    p_CcNode->keyAndNextEngineParams[i].nextEngineParams.params.ccParams.h_CcNode,
                    FALSE);

    if (p_CcNode->keyAndNextEngineParams[i].nextEngineParams.nextEngine
            == e_FM_PCD_CC)
        UpdateNodeOwner(
                p_CcNode->keyAndNextEngineParams[i].nextEngineParams.params.ccParams.h_CcNode,
                FALSE);

    /* Handle also Miss entry */
    for (i = 0; i < p_CcNode->numOfKeys + 1; i++)
    {
        if (p_CcNode->keyAndNextEngineParams[i].nextEngineParams.h_Manip)
            FmPcdManipUpdateOwner(
                    p_CcNode->keyAndNextEngineParams[i].nextEngineParams.h_Manip,
                    FALSE);

#if (DPAA_VERSION >= 11)
        if ((p_CcNode->keyAndNextEngineParams[i].nextEngineParams.nextEngine
                == e_FM_PCD_FR)
                && (p_CcNode->keyAndNextEngineParams[i].nextEngineParams.params.frParams.h_FrmReplic))
        {
            FrmReplicGroupUpdateOwner(
                    p_CcNode->keyAndNextEngineParams[i].nextEngineParams.params.frParams.h_FrmReplic,
                    FALSE);
        }
#endif /* (DPAA_VERSION >= 11) */
    }

    DeleteNode(p_CcNode);

    return E_OK;
}