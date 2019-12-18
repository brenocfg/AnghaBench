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
typedef  int uint32_t ;
struct TYPE_3__ {int exceptions; struct TYPE_3__* p_MemacDriverParam; } ;
typedef  TYPE_1__ t_Memac ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int /*<<< orphan*/  e_FmMacExceptions ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  GET_EXCEPTION_FLAG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error MemacConfigException(t_Handle h_Memac, e_FmMacExceptions exception, bool enable)
{
    t_Memac     *p_Memac = (t_Memac *)h_Memac;
    uint32_t    bitMask = 0;

    SANITY_CHECK_RETURN_ERROR(p_Memac, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_Memac->p_MemacDriverParam, E_INVALID_STATE);

    GET_EXCEPTION_FLAG(bitMask, exception);
    if (bitMask)
    {
        if (enable)
            p_Memac->exceptions |= bitMask;
        else
            p_Memac->exceptions &= ~bitMask;
    }
    else
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Undefined exception"));

    return E_OK;
}