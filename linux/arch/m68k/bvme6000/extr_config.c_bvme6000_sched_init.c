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
typedef  int /*<<< orphan*/  irq_handler_t ;
struct TYPE_2__ {int msr; int t1cr_omr; int t1msb; int t1lsb; int irr_icr1; int pfr_icr0; int t0cr_rtmr; } ;
typedef  TYPE_1__* RtcPtr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BVME_IRQ_ABORT ; 
 int /*<<< orphan*/  BVME_IRQ_RTC ; 
 int /*<<< orphan*/  BVME_RTC_BASE ; 
 int /*<<< orphan*/  IRQF_TIMER ; 
 int /*<<< orphan*/  RTC_TIMER_CLOCK_FREQ ; 
 int RTC_TIMER_COUNT ; 
 int /*<<< orphan*/  bvme6000_abort_int ; 
 int /*<<< orphan*/  bvme6000_clk ; 
 int /*<<< orphan*/  bvme6000_timer_int ; 
 int /*<<< orphan*/  clocksource_register_hz (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void bvme6000_sched_init (irq_handler_t timer_routine)
{
    volatile RtcPtr_t rtc = (RtcPtr_t)BVME_RTC_BASE;
    unsigned char msr = rtc->msr & 0xc0;

    rtc->msr = 0;	/* Ensure timer registers accessible */

    if (request_irq(BVME_IRQ_RTC, bvme6000_timer_int, IRQF_TIMER, "timer",
                    timer_routine))
	panic ("Couldn't register timer int");

    rtc->t1cr_omr = 0x04;	/* Mode 2, ext clk */
    rtc->t1msb = RTC_TIMER_COUNT >> 8;
    rtc->t1lsb = RTC_TIMER_COUNT & 0xff;
    rtc->irr_icr1 &= 0xef;	/* Route timer 1 to INTR pin */
    rtc->msr = 0x40;		/* Access int.cntrl, etc */
    rtc->pfr_icr0 = 0x80;	/* Just timer 1 ints enabled */
    rtc->irr_icr1 = 0;
    rtc->t1cr_omr = 0x0a;	/* INTR+T1 active lo, push-pull */
    rtc->t0cr_rtmr &= 0xdf;	/* Stop timers in standby */
    rtc->msr = 0;		/* Access timer 1 control */
    rtc->t1cr_omr = 0x05;	/* Mode 2, ext clk, GO */

    rtc->msr = msr;

    clocksource_register_hz(&bvme6000_clk, RTC_TIMER_CLOCK_FREQ);

    if (request_irq(BVME_IRQ_ABORT, bvme6000_abort_int, 0,
				"abort", bvme6000_abort_int))
	panic ("Couldn't register abort int");
}