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
struct rtc_time {int tm_year; int tm_sec; int tm_min; int tm_mday; int tm_mon; int tm_hour; } ;

/* Variables and functions */
 int /*<<< orphan*/  X1241REG_DT ; 
 int /*<<< orphan*/  X1241REG_HR ; 
 int X1241REG_HR_MIL ; 
 int /*<<< orphan*/  X1241REG_MN ; 
 int /*<<< orphan*/  X1241REG_MO ; 
 int /*<<< orphan*/  X1241REG_SC ; 
 int /*<<< orphan*/  X1241REG_SR ; 
 int X1241REG_SR_RWEL ; 
 int X1241REG_SR_WEL ; 
 int /*<<< orphan*/  X1241REG_Y2K ; 
 int /*<<< orphan*/  X1241REG_YR ; 
 void* bin2bcd (int) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int xicor_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xicor_write (int /*<<< orphan*/ ,int) ; 

int xicor_set_time(time64_t t)
{
	struct rtc_time tm;
	int tmp;
	unsigned long flags;

	rtc_time64_to_tm(t, &tm);
	tm.tm_year += 1900;

	spin_lock_irqsave(&rtc_lock, flags);
	/* unlock writes to the CCR */
	xicor_write(X1241REG_SR, X1241REG_SR_WEL);
	xicor_write(X1241REG_SR, X1241REG_SR_WEL | X1241REG_SR_RWEL);

	/* trivial ones */
	tm.tm_sec = bin2bcd(tm.tm_sec);
	xicor_write(X1241REG_SC, tm.tm_sec);

	tm.tm_min = bin2bcd(tm.tm_min);
	xicor_write(X1241REG_MN, tm.tm_min);

	tm.tm_mday = bin2bcd(tm.tm_mday);
	xicor_write(X1241REG_DT, tm.tm_mday);

	/* tm_mon starts from 0, *ick* */
	tm.tm_mon ++;
	tm.tm_mon = bin2bcd(tm.tm_mon);
	xicor_write(X1241REG_MO, tm.tm_mon);

	/* year is split */
	tmp = tm.tm_year / 100;
	tm.tm_year %= 100;
	xicor_write(X1241REG_YR, tm.tm_year);
	xicor_write(X1241REG_Y2K, tmp);

	/* hour is the most tricky one */
	tmp = xicor_read(X1241REG_HR);
	if (tmp & X1241REG_HR_MIL) {
		/* 24 hour format */
		tm.tm_hour = bin2bcd(tm.tm_hour);
		tmp = (tmp & ~0x3f) | (tm.tm_hour & 0x3f);
	} else {
		/* 12 hour format, with 0x2 for pm */
		tmp = tmp & ~0x3f;
		if (tm.tm_hour >= 12) {
			tmp |= 0x20;
			tm.tm_hour -= 12;
		}
		tm.tm_hour = bin2bcd(tm.tm_hour);
		tmp |= tm.tm_hour;
	}
	xicor_write(X1241REG_HR, tmp);

	xicor_write(X1241REG_SR, 0);
	spin_unlock_irqrestore(&rtc_lock, flags);

	return 0;
}