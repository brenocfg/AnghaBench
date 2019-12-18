#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_5__ {TYPE_1__* p_FmFpmRegs; } ;
typedef  TYPE_2__ t_Fm ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_4__ {int /*<<< orphan*/  fm_rstc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_MemoryBarrier () ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FPM_RSTC_FM_RESET ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_UDelay (int) ; 

t_Error FmReset(t_Handle h_Fm)
{
	t_Fm *p_Fm = (t_Fm*)h_Fm;

    SANITY_CHECK_RETURN_ERROR(p_Fm, E_INVALID_HANDLE);

    WRITE_UINT32(p_Fm->p_FmFpmRegs->fm_rstc, FPM_RSTC_FM_RESET);
    CORE_MemoryBarrier();
    XX_UDelay(100);

    return E_OK;
}