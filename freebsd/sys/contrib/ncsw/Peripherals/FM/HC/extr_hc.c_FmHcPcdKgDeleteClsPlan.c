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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_7__ {scalar_t__ numOfClsPlanEntries; int /*<<< orphan*/  baseEntry; } ;
typedef  TYPE_1__ t_FmPcdKgInterModuleClsPlanSet ;
struct TYPE_8__ {int /*<<< orphan*/  h_FmPcd; } ;
typedef  TYPE_2__ t_FmHc ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 scalar_t__ FM_PCD_MAX_NUM_OF_CLS_PLANS ; 
 scalar_t__ FmHcPcdKgSetClsPlan (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FmPcdKgDestroyClsPlanGrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdKgGetClsPlanGrpBase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FmPcdKgGetClsPlanGrpSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

t_Error FmHcPcdKgDeleteClsPlan(t_Handle h_FmHc, uint8_t  grpId)
{
    t_FmHc                              *p_FmHc = (t_FmHc*)h_FmHc;
    t_FmPcdKgInterModuleClsPlanSet      *p_ClsPlanSet;

    p_ClsPlanSet = (t_FmPcdKgInterModuleClsPlanSet *)XX_Malloc(sizeof(t_FmPcdKgInterModuleClsPlanSet));
    if (!p_ClsPlanSet)
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("Classification plan set"));

    memset(p_ClsPlanSet, 0, sizeof(t_FmPcdKgInterModuleClsPlanSet));

    p_ClsPlanSet->baseEntry = FmPcdKgGetClsPlanGrpBase(p_FmHc->h_FmPcd, grpId);
    p_ClsPlanSet->numOfClsPlanEntries = FmPcdKgGetClsPlanGrpSize(p_FmHc->h_FmPcd, grpId);
    ASSERT_COND(p_ClsPlanSet->numOfClsPlanEntries <= FM_PCD_MAX_NUM_OF_CLS_PLANS);

    if (FmHcPcdKgSetClsPlan(p_FmHc, p_ClsPlanSet) != E_OK)
    {
        XX_Free(p_ClsPlanSet);
        RETURN_ERROR(MAJOR, E_INVALID_STATE, NO_MSG);
    }

    XX_Free(p_ClsPlanSet);
    FmPcdKgDestroyClsPlanGrp(p_FmHc->h_FmPcd, grpId);

    return E_OK;
}