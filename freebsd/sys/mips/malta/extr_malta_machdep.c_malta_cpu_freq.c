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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ u_int64_t ;

/* Variables and functions */
 scalar_t__ MIPS_DEFAULT_HZ ; 
 int RTCSA_TUP ; 
 int RTCSB_BCD ; 
 int /*<<< orphan*/  RTC_STATUSA ; 
 int /*<<< orphan*/  RTC_STATUSB ; 
 scalar_t__ mips_rd_count () ; 
 int rtcin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writertc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ yamon_getcpufreq () ; 

__attribute__((used)) static uint64_t
malta_cpu_freq(void)
{
	uint64_t platform_counter_freq = 0;

#if defined(TICK_USE_YAMON_FREQ)
	/*
	 * If we are running on a board which uses YAMON firmware,
	 * then query CPU pipeline clock from the syscon object.
	 * If unsuccessful, use hard-coded default.
	 */
	platform_counter_freq = yamon_getcpufreq();

#elif defined(TICK_USE_MALTA_RTC)
	/*
	 * If we are running on a board with the MC146818 RTC,
	 * use it to determine CPU pipeline clock frequency.
	 */
	u_int64_t counterval[2];

	/* Set RTC to binary mode. */
	writertc(RTC_STATUSB, (rtcin(RTC_STATUSB) | RTCSB_BCD));

	/* Busy-wait for falling edge of RTC update. */
	while (((rtcin(RTC_STATUSA) & RTCSA_TUP) == 0))
		;
	while (((rtcin(RTC_STATUSA)& RTCSA_TUP) != 0))
		;
	counterval[0] = mips_rd_count();

	/* Busy-wait for falling edge of RTC update. */
	while (((rtcin(RTC_STATUSA) & RTCSA_TUP) == 0))
		;
	while (((rtcin(RTC_STATUSA)& RTCSA_TUP) != 0))
		;
	counterval[1] = mips_rd_count();

	platform_counter_freq = counterval[1] - counterval[0];
#endif

	if (platform_counter_freq == 0)
		platform_counter_freq = MIPS_DEFAULT_HZ;

	return (platform_counter_freq);
}