#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {int /*<<< orphan*/  h_Fm; struct TYPE_4__* p_RtcDriverParam; } ;
typedef  TYPE_1__ t_FmRtc ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FM_RTC_Disable (scalar_t__) ; 
 int /*<<< orphan*/  FmUnregisterIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_NORMAL ; 
 int /*<<< orphan*/  e_FM_MOD_TMR ; 

t_Error FM_RTC_Free(t_Handle h_FmRtc)
{
    t_FmRtc *p_Rtc = (t_FmRtc *)h_FmRtc;

    SANITY_CHECK_RETURN_ERROR(p_Rtc, E_INVALID_HANDLE);

    if (p_Rtc->p_RtcDriverParam)
    {
        XX_Free(p_Rtc->p_RtcDriverParam);
    }
    else
    {
        FM_RTC_Disable(h_FmRtc);
    }

    /* Unregister FM RTC interrupt */
    FmUnregisterIntr(p_Rtc->h_Fm, e_FM_MOD_TMR, 0, e_FM_INTR_TYPE_NORMAL);
    XX_Free(p_Rtc);

    return E_OK;
}