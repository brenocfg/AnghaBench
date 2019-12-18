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
struct rtc_time {unsigned int tm_sec; unsigned int tm_min; unsigned int tm_hour; unsigned int tm_mday; unsigned int tm_mon; unsigned int tm_year; unsigned int tm_wday; } ;

/* Variables and functions */
 void* CMOS_READ (int /*<<< orphan*/ ) ; 
 int HZ ; 
 scalar_t__ RTC_ALWAYS_BCD ; 
 int /*<<< orphan*/  RTC_CONTROL ; 
 int /*<<< orphan*/  RTC_DAY_OF_MONTH ; 
 int /*<<< orphan*/  RTC_DAY_OF_WEEK ; 
 int /*<<< orphan*/  RTC_DEC_YEAR ; 
 unsigned char RTC_DM_BINARY ; 
 int /*<<< orphan*/  RTC_HOURS ; 
 int /*<<< orphan*/  RTC_MINUTES ; 
 int /*<<< orphan*/  RTC_MONTH ; 
 int /*<<< orphan*/  RTC_SECONDS ; 
 int /*<<< orphan*/  RTC_YEAR ; 
 void* bcd2bin (unsigned int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int epoch ; 
 unsigned long jiffies ; 
 scalar_t__ rtc_is_updating () ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void rtc_get_rtc_time(struct rtc_time *rtc_tm)
{
	unsigned long uip_watchdog = jiffies, flags;
	unsigned char ctrl;
#ifdef CONFIG_MACH_DECSTATION
	unsigned int real_year;
#endif

	/*
	 * read RTC once any update in progress is done. The update
	 * can take just over 2ms. We wait 20ms. There is no need to
	 * to poll-wait (up to 1s - eeccch) for the falling edge of RTC_UIP.
	 * If you need to know *exactly* when a second has started, enable
	 * periodic update complete interrupts, (via ioctl) and then
	 * immediately read /dev/rtc which will block until you get the IRQ.
	 * Once the read clears, read the RTC time (again via ioctl). Easy.
	 */

	while (rtc_is_updating() != 0 &&
	       time_before(jiffies, uip_watchdog + 2*HZ/100))
		cpu_relax();

	/*
	 * Only the values that we read from the RTC are set. We leave
	 * tm_wday, tm_yday and tm_isdst untouched. Note that while the
	 * RTC has RTC_DAY_OF_WEEK, we should usually ignore it, as it is
	 * only updated by the RTC when initially set to a non-zero value.
	 */
	spin_lock_irqsave(&rtc_lock, flags);
	rtc_tm->tm_sec = CMOS_READ(RTC_SECONDS);
	rtc_tm->tm_min = CMOS_READ(RTC_MINUTES);
	rtc_tm->tm_hour = CMOS_READ(RTC_HOURS);
	rtc_tm->tm_mday = CMOS_READ(RTC_DAY_OF_MONTH);
	rtc_tm->tm_mon = CMOS_READ(RTC_MONTH);
	rtc_tm->tm_year = CMOS_READ(RTC_YEAR);
	/* Only set from 2.6.16 onwards */
	rtc_tm->tm_wday = CMOS_READ(RTC_DAY_OF_WEEK);

#ifdef CONFIG_MACH_DECSTATION
	real_year = CMOS_READ(RTC_DEC_YEAR);
#endif
	ctrl = CMOS_READ(RTC_CONTROL);
	spin_unlock_irqrestore(&rtc_lock, flags);

	if (!(ctrl & RTC_DM_BINARY) || RTC_ALWAYS_BCD) {
		rtc_tm->tm_sec = bcd2bin(rtc_tm->tm_sec);
		rtc_tm->tm_min = bcd2bin(rtc_tm->tm_min);
		rtc_tm->tm_hour = bcd2bin(rtc_tm->tm_hour);
		rtc_tm->tm_mday = bcd2bin(rtc_tm->tm_mday);
		rtc_tm->tm_mon = bcd2bin(rtc_tm->tm_mon);
		rtc_tm->tm_year = bcd2bin(rtc_tm->tm_year);
		rtc_tm->tm_wday = bcd2bin(rtc_tm->tm_wday);
	}

#ifdef CONFIG_MACH_DECSTATION
	rtc_tm->tm_year += real_year - 72;
#endif

	/*
	 * Account for differences between how the RTC uses the values
	 * and how they are defined in a struct rtc_time;
	 */
	rtc_tm->tm_year += epoch - 1900;
	if (rtc_tm->tm_year <= 69)
		rtc_tm->tm_year += 100;

	rtc_tm->tm_mon--;
}