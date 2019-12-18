#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_3__ {int noBuffCtxt; struct TYPE_3__* p_BmPoolDriverParams; } ;
typedef  TYPE_1__ t_BmPool ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 

t_Error  BM_POOL_ConfigBuffContextMode(t_Handle h_BmPool, bool en)
{
    t_BmPool            *p_BmPool   = (t_BmPool *)h_BmPool;

    SANITY_CHECK_RETURN_ERROR(p_BmPool, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_BmPool->p_BmPoolDriverParams, E_INVALID_HANDLE);

    p_BmPool->noBuffCtxt = !en;

    return E_OK;
}