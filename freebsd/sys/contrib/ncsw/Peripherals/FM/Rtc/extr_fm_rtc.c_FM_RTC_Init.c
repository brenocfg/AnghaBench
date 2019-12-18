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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {int srcClkFreqMhz; int clockPeriodNanoSec; struct rtc_cfg* p_RtcDriverParam; int /*<<< orphan*/  h_Fm; int /*<<< orphan*/  outputClockDivisor; struct rtc_regs* p_MemMap; } ;
typedef  TYPE_1__ t_FmRtc ;
typedef  scalar_t__ t_Error ;
struct rtc_regs {int dummy; } ;
struct rtc_cfg {scalar_t__ src_clk; int ext_src_clk_freq; scalar_t__ bypass; int /*<<< orphan*/  timer_slave_mode; } ;

/* Variables and functions */
 int ACCUMULATOR_OVERFLOW ; 
 scalar_t__ CheckInitParameters (TYPE_1__*) ; 
 scalar_t__ DIV_CEIL (int,int) ; 
 int /*<<< orphan*/  E_CONFLICT ; 
 scalar_t__ E_FMAN_RTC_SOURCE_CLOCK_SYSTEM ; 
 scalar_t__ E_OK ; 
 int FALSE ; 
 int /*<<< orphan*/  FM_RTC_NUM_OF_ALARMS ; 
 int /*<<< orphan*/  FM_RTC_NUM_OF_EXT_TRIGGERS ; 
 int /*<<< orphan*/  FM_RTC_NUM_OF_PERIODIC_PULSES ; 
 scalar_t__ FmGetMacClockFreq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmRegisterIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RtcExceptions ; 
 int TRUE ; 
 int /*<<< orphan*/  XX_Free (struct rtc_cfg*) ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_NORMAL ; 
 int /*<<< orphan*/  e_FM_MOD_TMR ; 
 int /*<<< orphan*/  fman_rtc_init (struct rtc_cfg*,struct rtc_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

t_Error FM_RTC_Init(t_Handle h_FmRtc)
{
    t_FmRtc             *p_Rtc = (t_FmRtc *)h_FmRtc;
    struct rtc_cfg      *p_RtcDriverParam;
    struct rtc_regs     *p_MemMap;
    uint32_t            freqCompensation = 0;
    uint64_t            tmpDouble;
    bool                init_freq_comp = FALSE;

    p_RtcDriverParam = p_Rtc->p_RtcDriverParam;
    p_MemMap = p_Rtc->p_MemMap;

    if (CheckInitParameters(p_Rtc)!=E_OK)
        RETURN_ERROR(MAJOR, E_CONFLICT,
                     ("Init Parameters are not Valid"));

    /* TODO check that no timestamping MACs are working in this stage. */

    /* find source clock frequency in Mhz */
    if (p_Rtc->p_RtcDriverParam->src_clk != E_FMAN_RTC_SOURCE_CLOCK_SYSTEM)
        p_Rtc->srcClkFreqMhz = p_Rtc->p_RtcDriverParam->ext_src_clk_freq;
    else
        p_Rtc->srcClkFreqMhz = (uint32_t)(FmGetMacClockFreq(p_Rtc->h_Fm));

    /* if timer in Master mode Initialize TMR_CTRL */
    /* We want the counter (TMR_CNT) to count in nano-seconds */
    if (!p_RtcDriverParam->timer_slave_mode && p_Rtc->p_RtcDriverParam->bypass)
        p_Rtc->clockPeriodNanoSec = (1000 / p_Rtc->srcClkFreqMhz);
    else
    {
        /* Initialize TMR_ADD with the initial frequency compensation value:
           freqCompensation = (2^32 / frequency ratio) */
        /* frequency ratio = sorce clock/rtc clock =
         * (p_Rtc->srcClkFreqMhz*1000000))/ 1/(p_Rtc->clockPeriodNanoSec * 1000000000) */
        init_freq_comp = TRUE;
        freqCompensation = (uint32_t)DIV_CEIL(ACCUMULATOR_OVERFLOW * 1000,
                                              p_Rtc->clockPeriodNanoSec * p_Rtc->srcClkFreqMhz);
    }

    /* check the legality of the relation between source and destination clocks */
    /* should be larger than 1.0001 */
    tmpDouble = 10000 * (uint64_t)p_Rtc->clockPeriodNanoSec * (uint64_t)p_Rtc->srcClkFreqMhz;
    if ((tmpDouble) <= 10001)
        RETURN_ERROR(MAJOR, E_CONFLICT,
              ("Invalid relation between source and destination clocks. Should be larger than 1.0001"));

    fman_rtc_init(p_RtcDriverParam,
             p_MemMap,
             FM_RTC_NUM_OF_ALARMS,
             FM_RTC_NUM_OF_PERIODIC_PULSES,
             FM_RTC_NUM_OF_EXT_TRIGGERS,
             init_freq_comp,
             freqCompensation,
             p_Rtc->outputClockDivisor);

    /* Register the FM RTC interrupt */
    FmRegisterIntr(p_Rtc->h_Fm, e_FM_MOD_TMR, 0, e_FM_INTR_TYPE_NORMAL, RtcExceptions , p_Rtc);

    /* Free parameters structures */
    XX_Free(p_Rtc->p_RtcDriverParam);
    p_Rtc->p_RtcDriverParam = NULL;

    return E_OK;
}