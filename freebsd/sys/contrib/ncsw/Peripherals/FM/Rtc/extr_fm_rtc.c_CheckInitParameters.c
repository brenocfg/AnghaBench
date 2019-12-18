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
struct TYPE_3__ {scalar_t__ outputClockDivisor; struct rtc_cfg* p_RtcDriverParam; } ;
typedef  TYPE_1__ t_FmRtc ;
typedef  int /*<<< orphan*/  t_Error ;
struct rtc_cfg {scalar_t__ src_clk; scalar_t__* alarm_polarity; scalar_t__* trigger_polarity; } ;

/* Variables and functions */
 scalar_t__ E_FMAN_RTC_ALARM_POLARITY_ACTIVE_HIGH ; 
 scalar_t__ E_FMAN_RTC_ALARM_POLARITY_ACTIVE_LOW ; 
 scalar_t__ E_FMAN_RTC_SOURCE_CLOCK_EXTERNAL ; 
 scalar_t__ E_FMAN_RTC_SOURCE_CLOCK_OSCILATOR ; 
 scalar_t__ E_FMAN_RTC_SOURCE_CLOCK_SYSTEM ; 
 scalar_t__ E_FMAN_RTC_TRIGGER_ON_FALLING_EDGE ; 
 scalar_t__ E_FMAN_RTC_TRIGGER_ON_RISING_EDGE ; 
 int /*<<< orphan*/  E_INVALID_CLOCK ; 
 int /*<<< orphan*/  E_INVALID_SELECTION ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int FM_RTC_NUM_OF_ALARMS ; 
 int FM_RTC_NUM_OF_EXT_TRIGGERS ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static t_Error CheckInitParameters(t_FmRtc *p_Rtc)
{
    struct rtc_cfg  *p_RtcDriverParam = p_Rtc->p_RtcDriverParam;
    int                 i;

    if ((p_RtcDriverParam->src_clk != E_FMAN_RTC_SOURCE_CLOCK_EXTERNAL) &&
        (p_RtcDriverParam->src_clk != E_FMAN_RTC_SOURCE_CLOCK_SYSTEM) &&
        (p_RtcDriverParam->src_clk != E_FMAN_RTC_SOURCE_CLOCK_OSCILATOR))
        RETURN_ERROR(MAJOR, E_INVALID_CLOCK, ("Source clock undefined"));

    if (p_Rtc->outputClockDivisor == 0)
    {
        RETURN_ERROR(MAJOR, E_INVALID_VALUE,
                     ("Divisor for output clock (should be positive)"));
    }

    for (i=0; i < FM_RTC_NUM_OF_ALARMS; i++)
    {
        if ((p_RtcDriverParam->alarm_polarity[i] != E_FMAN_RTC_ALARM_POLARITY_ACTIVE_LOW) &&
            (p_RtcDriverParam->alarm_polarity[i] != E_FMAN_RTC_ALARM_POLARITY_ACTIVE_HIGH))
        {
            RETURN_ERROR(MAJOR, E_INVALID_SELECTION, ("Alarm %d signal polarity", i));
        }
    }
    for (i=0; i < FM_RTC_NUM_OF_EXT_TRIGGERS; i++)
    {
        if ((p_RtcDriverParam->trigger_polarity[i] != E_FMAN_RTC_TRIGGER_ON_FALLING_EDGE) &&
            (p_RtcDriverParam->trigger_polarity[i] != E_FMAN_RTC_TRIGGER_ON_RISING_EDGE))
        {
            RETURN_ERROR(MAJOR, E_INVALID_SELECTION, ("Trigger %d signal polarity", i));
        }
    }

    return E_OK;
}