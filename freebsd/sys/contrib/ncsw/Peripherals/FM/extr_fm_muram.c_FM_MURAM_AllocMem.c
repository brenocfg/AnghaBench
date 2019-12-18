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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_2__ {scalar_t__ h_Mem; } ;
typedef  TYPE_1__ t_FmMuram ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 uintptr_t ILLEGAL_BASE ; 
 scalar_t__ MM_Get (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* UINT_TO_PTR (uintptr_t) ; 

void  * FM_MURAM_AllocMem(t_Handle h_FmMuram, uint32_t size, uint32_t align)
{
    t_FmMuram   *p_FmMuram = ( t_FmMuram *)h_FmMuram;
    uintptr_t   addr;

    SANITY_CHECK_RETURN_VALUE(h_FmMuram, E_INVALID_HANDLE, NULL);
    SANITY_CHECK_RETURN_VALUE(p_FmMuram->h_Mem, E_INVALID_HANDLE, NULL);

    addr = (uintptr_t)MM_Get(p_FmMuram->h_Mem, size, align ,"FM MURAM");

    if (addr == ILLEGAL_BASE)
        return NULL;

    return UINT_TO_PTR(addr);
}