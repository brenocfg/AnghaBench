#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_19__ {int numOfEntries; int numOfGrps; scalar_t__ p_Lock; scalar_t__ h_FmPcd; TYPE_6__* keyAndNextEngineParams; TYPE_1__* fmPcdGroupParam; scalar_t__ h_CapwapReassemblyManip; scalar_t__ h_IpReassemblyManip; scalar_t__ owners; int /*<<< orphan*/  netEnvId; } ;
typedef  TYPE_7__ t_FmPcdCcTree ;
typedef  TYPE_7__ t_FmPcd ;
typedef  scalar_t__ t_Error ;
struct TYPE_15__ {scalar_t__ h_FrmReplic; } ;
struct TYPE_14__ {scalar_t__ h_CcNode; } ;
struct TYPE_16__ {TYPE_3__ frParams; TYPE_2__ ccParams; } ;
struct TYPE_17__ {scalar_t__ nextEngine; TYPE_4__ params; scalar_t__ h_Manip; } ;
struct TYPE_18__ {TYPE_5__ nextEngineParams; } ;
struct TYPE_13__ {int numOfEntriesInGroup; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteTree (TYPE_7__*,TYPE_7__*) ; 
 scalar_t__ E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_SELECTION ; 
 scalar_t__ E_INVALID_STATE ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FM_PCD_ManipNodeDelete (scalar_t__) ; 
 int /*<<< orphan*/  FmPcdDecNetEnvOwners (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdManipDeleteCapwapReassmSchemes (scalar_t__) ; 
 int /*<<< orphan*/  FmPcdManipDeleteIpReassmSchemes (scalar_t__) ; 
 int /*<<< orphan*/  FmPcdManipUpdateOwner (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdReleaseLock (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FrmReplicGroupUpdateOwner (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ IsCapwapApplSpecific (scalar_t__) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  UpdateNodeOwner (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ e_FM_PCD_CC ; 
 scalar_t__ e_FM_PCD_FR ; 

t_Error FM_PCD_CcRootDelete(t_Handle h_CcTree)
{
    t_FmPcd *p_FmPcd;
    t_FmPcdCcTree *p_CcTree = (t_FmPcdCcTree *)h_CcTree;
    int i = 0;

    SANITY_CHECK_RETURN_ERROR(p_CcTree, E_INVALID_STATE);
    p_FmPcd = (t_FmPcd *)p_CcTree->h_FmPcd;
    SANITY_CHECK_RETURN_ERROR(p_FmPcd, E_INVALID_HANDLE);

    FmPcdDecNetEnvOwners(p_FmPcd, p_CcTree->netEnvId);

    if (p_CcTree->owners)
        RETURN_ERROR(
                MAJOR,
                E_INVALID_SELECTION,
                ("the tree with this ID can not be removed because this tree is occupied, first - unbind this tree"));

    /* Delete ip-reassembly schemes if exist */
    if (p_CcTree->h_IpReassemblyManip)
    {
        FmPcdManipDeleteIpReassmSchemes(p_CcTree->h_IpReassemblyManip);
        FmPcdManipUpdateOwner(p_CcTree->h_IpReassemblyManip, FALSE);
    }

    /* Delete capwap-reassembly schemes if exist */
    if (p_CcTree->h_CapwapReassemblyManip)
    {
        FmPcdManipDeleteCapwapReassmSchemes(p_CcTree->h_CapwapReassemblyManip);
        FmPcdManipUpdateOwner(p_CcTree->h_CapwapReassemblyManip, FALSE);
    }

    for (i = 0; i < p_CcTree->numOfEntries; i++)
    {
        if (p_CcTree->keyAndNextEngineParams[i].nextEngineParams.nextEngine
                == e_FM_PCD_CC)
            UpdateNodeOwner(
                    p_CcTree->keyAndNextEngineParams[i].nextEngineParams.params.ccParams.h_CcNode,
                    FALSE);

        if (p_CcTree->keyAndNextEngineParams[i].nextEngineParams.h_Manip)
            FmPcdManipUpdateOwner(
                    p_CcTree->keyAndNextEngineParams[i].nextEngineParams.h_Manip,
                    FALSE);

#ifdef FM_CAPWAP_SUPPORT
        if ((p_CcTree->numOfGrps == 1) &&
                (p_CcTree->fmPcdGroupParam[0].numOfEntriesInGroup == 1) &&
                (p_CcTree->keyAndNextEngineParams[0].nextEngineParams.nextEngine == e_FM_PCD_CC) &&
                p_CcTree->keyAndNextEngineParams[0].nextEngineParams.params.ccParams.h_CcNode &&
                IsCapwapApplSpecific(p_CcTree->keyAndNextEngineParams[0].nextEngineParams.params.ccParams.h_CcNode))
        {
            if (FM_PCD_ManipNodeDelete(p_CcTree->keyAndNextEngineParams[0].nextEngineParams.h_Manip) != E_OK)
            return E_INVALID_STATE;
        }
#endif /* FM_CAPWAP_SUPPORT */

#if (DPAA_VERSION >= 11)
        if ((p_CcTree->keyAndNextEngineParams[i].nextEngineParams.nextEngine
                == e_FM_PCD_FR)
                && (p_CcTree->keyAndNextEngineParams[i].nextEngineParams.params.frParams.h_FrmReplic))
            FrmReplicGroupUpdateOwner(
                    p_CcTree->keyAndNextEngineParams[i].nextEngineParams.params.frParams.h_FrmReplic,
                    FALSE);
#endif /* (DPAA_VERSION >= 11) */
    }

    if (p_CcTree->p_Lock)
        FmPcdReleaseLock(p_CcTree->h_FmPcd, p_CcTree->p_Lock);

    DeleteTree(p_CcTree, p_FmPcd);

    return E_OK;
}