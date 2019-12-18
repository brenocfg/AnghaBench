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
struct TYPE_3__ {int wan_mode_enable; struct TYPE_3__* p_MemacDriverParam; } ;
typedef  TYPE_1__ t_Memac ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error MemacConfigWan(t_Handle h_Memac, bool newVal)
{
    t_Memac     *p_Memac = (t_Memac *)h_Memac;

    SANITY_CHECK_RETURN_ERROR(p_Memac, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_Memac->p_MemacDriverParam, E_INVALID_STATE);

    p_Memac->p_MemacDriverParam->wan_mode_enable = newVal;

    return E_OK;
}