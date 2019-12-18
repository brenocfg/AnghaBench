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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  rtFramesDepth; struct TYPE_3__* p_QmDriverParams; } ;
typedef  TYPE_1__ t_Qm ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 

t_Error QM_ConfigRTFramesDepth(t_Handle h_Qm, uint32_t rtFramesDepth)
{
    t_Qm        *p_Qm = (t_Qm *)h_Qm;

    SANITY_CHECK_RETURN_ERROR(p_Qm, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_Qm->p_QmDriverParams, E_INVALID_HANDLE);

    p_Qm->p_QmDriverParams->rtFramesDepth = rtFramesDepth;

    return E_OK;
}