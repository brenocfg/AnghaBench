#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ JZ_TCU_BASE ; 
 scalar_t__ JZ_WDOG_TCER ; 
 scalar_t__ JZ_WDOG_TCNT ; 
 scalar_t__ JZ_WDOG_TCSR ; 
 scalar_t__ JZ_WDOG_TDR ; 
 int TCER_ENABLE ; 
 int TCSR_DIV_256 ; 
 int TCSR_RTC_EN ; 
 int /*<<< orphan*/  writereg (scalar_t__,int) ; 

void
platform_reset(void)
{
	/*
	 * For now, provoke a watchdog reset in about a second, so UART buffers
	 * have a fighting chance to flush before we pull the plug
	 */
	writereg(JZ_TCU_BASE + JZ_WDOG_TCER, 0);	/* disable watchdog */
	writereg(JZ_TCU_BASE + JZ_WDOG_TCNT, 0);	/* reset counter */
	writereg(JZ_TCU_BASE + JZ_WDOG_TDR, 128);	/* wait for ~1s */
	writereg(JZ_TCU_BASE + JZ_WDOG_TCSR, TCSR_RTC_EN | TCSR_DIV_256);
	writereg(JZ_TCU_BASE + JZ_WDOG_TCER, TCER_ENABLE);	/* fire! */

	/* Wait for reset */
	while (1)
		;
}