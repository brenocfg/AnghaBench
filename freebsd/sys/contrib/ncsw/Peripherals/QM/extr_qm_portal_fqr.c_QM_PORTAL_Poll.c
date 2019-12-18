#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* f_LoopDequeueRingCB ) (scalar_t__) ;int /*<<< orphan*/  p_LowQmPortal; } ;
typedef  TYPE_1__ t_QmPortal ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  scalar_t__ e_QmPortalPollSource ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ LoopMessageRing (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  NCSW_PLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  PUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ e_QM_PORTAL_POLL_SOURCE_BOTH ; 
 scalar_t__ e_QM_PORTAL_POLL_SOURCE_CONTROL_FRAMES ; 
 scalar_t__ e_QM_PORTAL_POLL_SOURCE_DATA_FRAMES ; 
 int /*<<< orphan*/  qm_isr_status_clear (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ qm_isr_status_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

t_Error QM_PORTAL_Poll(t_Handle h_QmPortal, e_QmPortalPollSource source)
{
    t_QmPortal  *p_QmPortal = (t_QmPortal *)h_QmPortal;

    SANITY_CHECK_RETURN_ERROR(p_QmPortal, E_INVALID_HANDLE);

    NCSW_PLOCK(p_QmPortal);

    if ((source == e_QM_PORTAL_POLL_SOURCE_CONTROL_FRAMES) ||
        (source == e_QM_PORTAL_POLL_SOURCE_BOTH))
    {
        uint32_t is = qm_isr_status_read(p_QmPortal->p_LowQmPortal);
        uint32_t active = LoopMessageRing(p_QmPortal, is);
        if (active)
            qm_isr_status_clear(p_QmPortal->p_LowQmPortal, active);
    }
    if ((source == e_QM_PORTAL_POLL_SOURCE_DATA_FRAMES) ||
        (source == e_QM_PORTAL_POLL_SOURCE_BOTH))
        p_QmPortal->f_LoopDequeueRingCB((t_Handle)p_QmPortal);

    PUNLOCK(p_QmPortal);

    return E_OK;
}