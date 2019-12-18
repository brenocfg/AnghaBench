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
typedef  int /*<<< orphan*/  time64_t ;

/* Variables and functions */
 int /*<<< orphan*/  M41T81REG_DT ; 
 int /*<<< orphan*/  M41T81REG_HR ; 
 int /*<<< orphan*/  M41T81REG_MN ; 
 int /*<<< orphan*/  M41T81REG_MO ; 
 int /*<<< orphan*/  M41T81REG_SC ; 
 int /*<<< orphan*/  M41T81REG_YR ; 
 unsigned int bcd2bin (unsigned int) ; 
 int m41t81_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mktime64 (unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

time64_t m41t81_get_time(void)
{
	unsigned int year, mon, day, hour, min, sec;
	unsigned long flags;

	/*
	 * min is valid if two reads of sec are the same.
	 */
	for (;;) {
		spin_lock_irqsave(&rtc_lock, flags);
		sec = m41t81_read(M41T81REG_SC);
		min = m41t81_read(M41T81REG_MN);
		if (sec == m41t81_read(M41T81REG_SC)) break;
		spin_unlock_irqrestore(&rtc_lock, flags);
	}
	hour = m41t81_read(M41T81REG_HR) & 0x3f;
	day = m41t81_read(M41T81REG_DT);
	mon = m41t81_read(M41T81REG_MO);
	year = m41t81_read(M41T81REG_YR);
	spin_unlock_irqrestore(&rtc_lock, flags);

	sec = bcd2bin(sec);
	min = bcd2bin(min);
	hour = bcd2bin(hour);
	day = bcd2bin(day);
	mon = bcd2bin(mon);
	year = bcd2bin(year);

	year += 2000;

	return mktime64(year, mon, day, hour, min, sec);
}