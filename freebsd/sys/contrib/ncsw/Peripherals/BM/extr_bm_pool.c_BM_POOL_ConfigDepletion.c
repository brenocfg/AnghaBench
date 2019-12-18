#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_5__ {int /*<<< orphan*/  depletionThresholds; struct TYPE_5__* p_BmPoolDriverParams; struct TYPE_5__* f_Depletion; int /*<<< orphan*/  useDepletion; } ;
typedef  TYPE_1__ t_BmPool ;
typedef  TYPE_1__ t_BmDepletionCallback ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

t_Error  BM_POOL_ConfigDepletion(t_Handle h_BmPool, t_BmDepletionCallback *f_Depletion, uint32_t *p_Thresholds)
{
    t_BmPool            *p_BmPool   = (t_BmPool *)h_BmPool;

    SANITY_CHECK_RETURN_ERROR(p_BmPool, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_BmPool->p_BmPoolDriverParams, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(f_Depletion, E_INVALID_HANDLE);

    p_BmPool->p_BmPoolDriverParams->useDepletion = TRUE;
    p_BmPool->f_Depletion = f_Depletion;
    memcpy(&p_BmPool->p_BmPoolDriverParams->depletionThresholds,
           p_Thresholds,
           sizeof(p_BmPool->p_BmPoolDriverParams->depletionThresholds));

    return E_OK;
}