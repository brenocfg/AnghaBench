#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timespec64 {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_3__ {scalar_t__ revision; } ;
struct TYPE_4__ {scalar_t__ century; TYPE_1__ header; } ;

/* Variables and functions */
 int CMOS_READ (scalar_t__) ; 
 scalar_t__ CMOS_YEARS_OFFS ; 
 scalar_t__ FADT2_REVISION_ID ; 
 scalar_t__ RTC_ALWAYS_BCD ; 
 scalar_t__ RTC_CONTROL ; 
 scalar_t__ RTC_DAY_OF_MONTH ; 
 unsigned int RTC_DM_BINARY ; 
 scalar_t__ RTC_FREQ_SELECT ; 
 scalar_t__ RTC_HOURS ; 
 scalar_t__ RTC_MINUTES ; 
 scalar_t__ RTC_MONTH ; 
 scalar_t__ RTC_SECONDS ; 
 int RTC_UIP ; 
 scalar_t__ RTC_YEAR ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 TYPE_2__ acpi_gbl_FADT ; 
 unsigned int bcd2bin (unsigned int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ mktime64 (unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pm_trace_rtc_valid () ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mach_get_cmos_time(struct timespec64 *now)
{
	unsigned int status, year, mon, day, hour, min, sec, century = 0;
	unsigned long flags;

	/*
	 * If pm_trace abused the RTC as storage, set the timespec to 0,
	 * which tells the caller that this RTC value is unusable.
	 */
	if (!pm_trace_rtc_valid()) {
		now->tv_sec = now->tv_nsec = 0;
		return;
	}

	spin_lock_irqsave(&rtc_lock, flags);

	/*
	 * If UIP is clear, then we have >= 244 microseconds before
	 * RTC registers will be updated.  Spec sheet says that this
	 * is the reliable way to read RTC - registers. If UIP is set
	 * then the register access might be invalid.
	 */
	while ((CMOS_READ(RTC_FREQ_SELECT) & RTC_UIP))
		cpu_relax();

	sec = CMOS_READ(RTC_SECONDS);
	min = CMOS_READ(RTC_MINUTES);
	hour = CMOS_READ(RTC_HOURS);
	day = CMOS_READ(RTC_DAY_OF_MONTH);
	mon = CMOS_READ(RTC_MONTH);
	year = CMOS_READ(RTC_YEAR);

#ifdef CONFIG_ACPI
	if (acpi_gbl_FADT.header.revision >= FADT2_REVISION_ID &&
	    acpi_gbl_FADT.century)
		century = CMOS_READ(acpi_gbl_FADT.century);
#endif

	status = CMOS_READ(RTC_CONTROL);
	WARN_ON_ONCE(RTC_ALWAYS_BCD && (status & RTC_DM_BINARY));

	spin_unlock_irqrestore(&rtc_lock, flags);

	if (RTC_ALWAYS_BCD || !(status & RTC_DM_BINARY)) {
		sec = bcd2bin(sec);
		min = bcd2bin(min);
		hour = bcd2bin(hour);
		day = bcd2bin(day);
		mon = bcd2bin(mon);
		year = bcd2bin(year);
	}

	if (century) {
		century = bcd2bin(century);
		year += century * 100;
	} else
		year += CMOS_YEARS_OFFS;

	now->tv_sec = mktime64(year, mon, day, hour, min, sec);
	now->tv_nsec = 0;
}