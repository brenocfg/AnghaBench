#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_2__ {scalar_t__ h_Mem; } ;
typedef  TYPE_1__ t_FmMuram ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_ADDRESS ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ MM_Put (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_TO_UINT (void*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (scalar_t__,int /*<<< orphan*/ ) ; 

t_Error FM_MURAM_FreeMem(t_Handle h_FmMuram, void *ptr)
{
    t_FmMuram   *p_FmMuram = ( t_FmMuram *)h_FmMuram;

    SANITY_CHECK_RETURN_ERROR(h_FmMuram, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_FmMuram->h_Mem, E_INVALID_HANDLE);

    if (MM_Put(p_FmMuram->h_Mem, PTR_TO_UINT(ptr)) == 0)
        RETURN_ERROR(MINOR, E_INVALID_ADDRESS, ("memory pointer!!!"));

    return E_OK;
}