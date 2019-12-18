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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {scalar_t__ numOfKeys; int /*<<< orphan*/  h_Spinlock; } ;
typedef  TYPE_1__ t_FmPcdCcNode ;
typedef  int /*<<< orphan*/  t_FmPcdCcKeyStatistics ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  E_NULL_POINTER ; 
 scalar_t__ E_OK ; 
 scalar_t__ FindKeyIndex (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ GET_ERROR_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ MatchTableGetKeyStatistics (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_LockIntrSpinlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

t_Error FM_PCD_MatchTableFindNGetKeyStatistics(
        t_Handle h_CcNode, uint8_t keySize, uint8_t *p_Key, uint8_t *p_Mask,
        t_FmPcdCcKeyStatistics *p_KeyStatistics)
{
    t_FmPcdCcNode *p_CcNode = (t_FmPcdCcNode *)h_CcNode;
    uint16_t keyIndex;
    uint32_t intFlags;
    t_Error err;

    SANITY_CHECK_RETURN_ERROR(p_Key, E_NULL_POINTER);
    SANITY_CHECK_RETURN_ERROR(p_KeyStatistics, E_NULL_POINTER);

    intFlags = XX_LockIntrSpinlock(p_CcNode->h_Spinlock);

    err = FindKeyIndex(p_CcNode, keySize, p_Key, p_Mask, &keyIndex);
    if (GET_ERROR_TYPE(err) != E_OK)
    {
        XX_UnlockIntrSpinlock(p_CcNode->h_Spinlock, intFlags);
        RETURN_ERROR(MAJOR, err,
                     ("The received key and mask pair was not found in the "
                     "match table of the provided node"));
    }

    ASSERT_COND(keyIndex < p_CcNode->numOfKeys);

    err = MatchTableGetKeyStatistics(p_CcNode, keyIndex, p_KeyStatistics);

    XX_UnlockIntrSpinlock(p_CcNode->h_Spinlock, intFlags);

    if (err != E_OK)
        RETURN_ERROR(MAJOR, err, NO_MSG);

    return E_OK;
}