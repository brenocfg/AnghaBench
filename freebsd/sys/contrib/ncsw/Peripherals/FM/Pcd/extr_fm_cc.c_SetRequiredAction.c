#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  t_Handle ;
typedef  int /*<<< orphan*/  t_FmPcdCcKeyAndNextEngineParams ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 scalar_t__ E_OK ; 
 scalar_t__ SetRequiredAction1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_CC_SHADOW_CLEAR ; 

__attribute__((used)) static t_Error SetRequiredAction(
        t_Handle h_FmPcd, uint32_t requiredAction,
        t_FmPcdCcKeyAndNextEngineParams *p_CcKeyAndNextEngineParamsTmp,
        t_Handle h_AdTmp, uint16_t numOfEntries, t_Handle h_Tree)
{
    t_Error err = SetRequiredAction1(h_FmPcd, requiredAction,
                                     p_CcKeyAndNextEngineParamsTmp, h_AdTmp,
                                     numOfEntries, h_Tree);
    if (err != E_OK)
        return err;
    return SetRequiredAction1(h_FmPcd, UPDATE_CC_SHADOW_CLEAR,
                              p_CcKeyAndNextEngineParamsTmp, h_AdTmp,
                              numOfEntries, h_Tree);
}