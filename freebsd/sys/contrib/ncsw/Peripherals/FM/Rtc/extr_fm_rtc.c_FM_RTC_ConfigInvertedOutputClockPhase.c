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
typedef  scalar_t__ t_Handle ;
struct TYPE_3__ {int invert_output_clk_phase; struct TYPE_3__* p_RtcDriverParam; } ;
typedef  TYPE_1__ t_FmRtc ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 

t_Error FM_RTC_ConfigInvertedOutputClockPhase(t_Handle h_FmRtc, bool inverted)
{
    t_FmRtc *p_Rtc = (t_FmRtc *)h_FmRtc;

    SANITY_CHECK_RETURN_ERROR(p_Rtc, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_Rtc->p_RtcDriverParam, E_INVALID_STATE);

    p_Rtc->p_RtcDriverParam->invert_output_clk_phase = inverted;

    return E_OK;
}