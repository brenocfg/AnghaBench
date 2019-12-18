#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_5__ {int /*<<< orphan*/  h_Spinlock; scalar_t__ h_FmPcd; scalar_t__ h_Ad; scalar_t__ h_TmpAd; scalar_t__ maxNumOfKeys; } ;
typedef  TYPE_1__ t_FmPcdCcNode ;
struct TYPE_6__ {int /*<<< orphan*/  h_FmMuram; } ;
typedef  TYPE_2__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ FM_MURAM_AllocMem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_ENTRY_SIZE ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_TABLE_ALIGN ; 
 int /*<<< orphan*/  FillAdOfTypeContLookup (scalar_t__,int /*<<< orphan*/ *,scalar_t__,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MemSet8 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XX_LockIntrSpinlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error AllocAndFillAdForContLookupManip(t_Handle h_CcNode)
{
    t_FmPcdCcNode *p_CcNode = (t_FmPcdCcNode *)h_CcNode;
    uint32_t intFlags;

    ASSERT_COND(p_CcNode);

    intFlags = XX_LockIntrSpinlock(p_CcNode->h_Spinlock);

    if (!p_CcNode->h_Ad)
    {
        if (p_CcNode->maxNumOfKeys)
            p_CcNode->h_Ad = p_CcNode->h_TmpAd;
        else
            p_CcNode->h_Ad = (t_Handle)FM_MURAM_AllocMem(
                    ((t_FmPcd *)(p_CcNode->h_FmPcd))->h_FmMuram,
                    FM_PCD_CC_AD_ENTRY_SIZE, FM_PCD_CC_AD_TABLE_ALIGN);

        XX_UnlockIntrSpinlock(p_CcNode->h_Spinlock, intFlags);

        if (!p_CcNode->h_Ad)
            RETURN_ERROR(MAJOR, E_NO_MEMORY,
                         ("MURAM allocation for CC action descriptor"));

        MemSet8(p_CcNode->h_Ad, 0, FM_PCD_CC_AD_ENTRY_SIZE);

        FillAdOfTypeContLookup(p_CcNode->h_Ad, NULL, p_CcNode->h_FmPcd,
                               p_CcNode, NULL, NULL);
    }
    else
        XX_UnlockIntrSpinlock(p_CcNode->h_Spinlock, intFlags);

    return E_OK;
}