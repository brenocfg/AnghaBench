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
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_3__ {int exceptions; struct TYPE_3__* p_BmDriverParams; } ;
typedef  TYPE_1__ t_Bm ;
typedef  int /*<<< orphan*/  e_BmExceptions ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  GET_EXCEPTION_FLAG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 

t_Error BM_ConfigException(t_Handle h_Bm, e_BmExceptions exception, bool enable)
{
    t_Bm                *p_Bm = (t_Bm*)h_Bm;
    uint32_t            bitMask = 0;

    SANITY_CHECK_RETURN_ERROR(p_Bm, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_Bm->p_BmDriverParams, E_INVALID_HANDLE);

    GET_EXCEPTION_FLAG(bitMask, exception);
    if(bitMask)
    {
        if (enable)
            p_Bm->exceptions |= bitMask;
        else
            p_Bm->exceptions &= ~bitMask;
   }
    else
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Undefined exception"));

    return E_OK;
}