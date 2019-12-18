#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int ccKeySizeAccExtraction; int maxNumOfKeys; int /*<<< orphan*/  h_FmPcd; scalar_t__ maskSupport; } ;
typedef  TYPE_1__ t_FmPcdCcNode ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteNode (TYPE_1__*) ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 int FM_PCD_CC_AD_ENTRY_SIZE ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_TABLE_ALIGN ; 
 scalar_t__ FmPcdUpdateCcShadow (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static t_Error CalcAndUpdateCcShadow(t_FmPcdCcNode *p_CcNode,
                                     bool isKeyTblAlloc,
                                     uint32_t *p_MatchTableSize,
                                     uint32_t *p_AdTableSize)
{
    uint32_t shadowSize;
    t_Error err;

    /* Calculate keys table maximal size - each entry consists of a key and a mask,
     (if local mask support is requested) */
    *p_MatchTableSize = p_CcNode->ccKeySizeAccExtraction * sizeof(uint8_t)
            * p_CcNode->maxNumOfKeys;

    if (p_CcNode->maskSupport)
        *p_MatchTableSize *= 2;

    /* Calculate next action descriptors table, including one more entry for miss */
    *p_AdTableSize = (uint32_t)((p_CcNode->maxNumOfKeys + 1)
            * FM_PCD_CC_AD_ENTRY_SIZE);

    /* Calculate maximal shadow size of this node.
     All shadow structures will be used for runtime modifications host command. If
     keys table was allocated for this node, the keys table and next engines table may
     be modified in run time (entries added or removed), so shadow tables are requires.
     Otherwise, the only supported runtime modification is a specific next engine update
     and this requires shadow memory of a single AD */

    /* Shadow size should be enough to hold the following 3 structures:
     * 1 - an action descriptor */
    shadowSize = FM_PCD_CC_AD_ENTRY_SIZE;

    /* 2 - keys match table, if was allocated for the current node */
    if (isKeyTblAlloc)
        shadowSize += *p_MatchTableSize;

    /* 3 - next action descriptors table */
    shadowSize += *p_AdTableSize;

    /* Update shadow to the calculated size */
    err = FmPcdUpdateCcShadow(p_CcNode->h_FmPcd, (uint32_t)shadowSize,
                              FM_PCD_CC_AD_TABLE_ALIGN);
    if (err != E_OK)
    {
        DeleteNode(p_CcNode);
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("MURAM allocation for CC node shadow"));
    }

    return E_OK;
}