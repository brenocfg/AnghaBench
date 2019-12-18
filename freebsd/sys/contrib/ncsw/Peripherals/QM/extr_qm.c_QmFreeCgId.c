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
typedef  size_t uint8_t ;
struct TYPE_2__ {size_t* cgsUsed; } ;
typedef  TYPE_1__ t_Qm ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

t_Error QmFreeCgId(t_Handle h_Qm, uint8_t cgId)
{
    t_Qm        *p_Qm = (t_Qm *)h_Qm;

    if (!p_Qm->cgsUsed[cgId])
        RETURN_ERROR(MINOR, E_INVALID_STATE, ("CG is not in use"));
    else
        p_Qm->cgsUsed[cgId] = (uint8_t)FALSE;

    return E_OK;
}