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
typedef  struct rtc_cfg* t_Handle ;
struct TYPE_4__ {int /*<<< orphan*/  h_App; int /*<<< orphan*/  baseAddress; int /*<<< orphan*/  h_Fm; } ;
typedef  TYPE_1__ t_FmRtcParams ;
struct rtc_cfg {int /*<<< orphan*/  h_App; struct rtc_regs* p_MemMap; int /*<<< orphan*/  clockPeriodNanoSec; int /*<<< orphan*/  bypass; struct rtc_cfg* p_RtcDriverParam; int /*<<< orphan*/  outputClockDivisor; int /*<<< orphan*/  h_Fm; } ;
typedef  struct rtc_cfg t_FmRtc ;
struct rtc_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BYPASS ; 
 int /*<<< orphan*/  DEFAULT_CLOCK_PERIOD ; 
 int /*<<< orphan*/  DEFAULT_OUTPUT_CLOCK_DIVISOR ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_NULL_POINTER ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ UINT_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_Free (struct rtc_cfg*) ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  fman_rtc_defconfig (struct rtc_cfg*) ; 
 int /*<<< orphan*/  memset (struct rtc_cfg*,int /*<<< orphan*/ ,int) ; 

t_Handle FM_RTC_Config(t_FmRtcParams *p_FmRtcParam)
{
    t_FmRtc *p_Rtc;

    SANITY_CHECK_RETURN_VALUE(p_FmRtcParam, E_NULL_POINTER, NULL);

    /* Allocate memory for the FM RTC driver parameters */
    p_Rtc = (t_FmRtc *)XX_Malloc(sizeof(t_FmRtc));
    if (!p_Rtc)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM RTC driver structure"));
        return NULL;
    }

    memset(p_Rtc, 0, sizeof(t_FmRtc));

    /* Allocate memory for the FM RTC driver parameters */
    p_Rtc->p_RtcDriverParam = (struct rtc_cfg *)XX_Malloc(sizeof(struct rtc_cfg));
    if (!p_Rtc->p_RtcDriverParam)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM RTC driver parameters"));
        XX_Free(p_Rtc);
        return NULL;
    }

    memset(p_Rtc->p_RtcDriverParam, 0, sizeof(struct rtc_cfg));

    /* Store RTC configuration parameters */
    p_Rtc->h_Fm = p_FmRtcParam->h_Fm;

    /* Set default RTC configuration parameters */
    fman_rtc_defconfig(p_Rtc->p_RtcDriverParam);

    p_Rtc->outputClockDivisor = DEFAULT_OUTPUT_CLOCK_DIVISOR;
    p_Rtc->p_RtcDriverParam->bypass = DEFAULT_BYPASS;
    p_Rtc->clockPeriodNanoSec = DEFAULT_CLOCK_PERIOD; /* 1 usec */


    /* Store RTC parameters in the RTC control structure */
    p_Rtc->p_MemMap = (struct rtc_regs *)UINT_TO_PTR(p_FmRtcParam->baseAddress);
    p_Rtc->h_App    = p_FmRtcParam->h_App;

    return p_Rtc;
}