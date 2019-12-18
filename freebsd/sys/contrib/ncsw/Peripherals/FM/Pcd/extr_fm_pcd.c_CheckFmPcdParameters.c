#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ guestId; TYPE_3__* p_FmPcdDriverParam; TYPE_2__* p_FmPcdKg; TYPE_1__* p_FmPcdPlcr; int /*<<< orphan*/  f_FmPcdIndexedException; int /*<<< orphan*/  f_Exception; int /*<<< orphan*/  h_Fm; } ;
typedef  TYPE_4__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_8__ {scalar_t__ prsMaxParseCycleLimit; } ;
struct TYPE_7__ {int /*<<< orphan*/  p_FmPcdKgRegs; } ;
struct TYPE_6__ {int /*<<< orphan*/  p_FmPcdPlcrRegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 scalar_t__ PRS_MAX_CYCLE_LIMIT ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static t_Error CheckFmPcdParameters(t_FmPcd *p_FmPcd)
{
    if (!p_FmPcd->h_Fm)
         RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("h_Fm has to be initialized"));

    if (p_FmPcd->guestId == NCSW_MASTER_ID)
    {
        if (p_FmPcd->p_FmPcdKg && !p_FmPcd->p_FmPcdKg->p_FmPcdKgRegs)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Something WRONG"));

        if (p_FmPcd->p_FmPcdPlcr && !p_FmPcd->p_FmPcdPlcr->p_FmPcdPlcrRegs)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Something WRONG"));

        if (!p_FmPcd->f_Exception)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("f_FmPcdExceptions has to be initialized"));

        if ((!p_FmPcd->f_FmPcdIndexedException) && (p_FmPcd->p_FmPcdPlcr || p_FmPcd->p_FmPcdKg))
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("f_FmPcdIndexedException has to be initialized"));

        if (p_FmPcd->p_FmPcdDriverParam->prsMaxParseCycleLimit > PRS_MAX_CYCLE_LIMIT)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("prsMaxParseCycleLimit has to be less than 8191"));
    }

    return E_OK;
}