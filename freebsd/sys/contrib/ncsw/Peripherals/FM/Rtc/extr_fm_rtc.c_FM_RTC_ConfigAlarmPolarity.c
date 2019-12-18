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
typedef  size_t uint8_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_3__ {int* alarm_polarity; struct TYPE_3__* p_RtcDriverParam; } ;
typedef  TYPE_1__ t_FmRtc ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  enum fman_rtc_alarm_polarity { ____Placeholder_fman_rtc_alarm_polarity } fman_rtc_alarm_polarity ;
typedef  scalar_t__ e_FmRtcAlarmPolarity ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_SELECTION ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 size_t FM_RTC_NUM_OF_ALARMS ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 

t_Error FM_RTC_ConfigAlarmPolarity(t_Handle             h_FmRtc,
                                   uint8_t              alarmId,
                                   e_FmRtcAlarmPolarity alarmPolarity)
{
    t_FmRtc *p_Rtc = (t_FmRtc *)h_FmRtc;

    SANITY_CHECK_RETURN_ERROR(p_Rtc, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_Rtc->p_RtcDriverParam, E_INVALID_STATE);

    if (alarmId >= FM_RTC_NUM_OF_ALARMS)
        RETURN_ERROR(MAJOR, E_INVALID_SELECTION, ("Alarm ID"));

    p_Rtc->p_RtcDriverParam->alarm_polarity[alarmId] =
        (enum fman_rtc_alarm_polarity)alarmPolarity;

    return E_OK;
}