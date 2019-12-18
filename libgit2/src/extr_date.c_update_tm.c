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
typedef  scalar_t__ time_t ;
struct tm {scalar_t__ tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
typedef  scalar_t__ git_time_t ;

/* Variables and functions */
 scalar_t__ mktime (struct tm*) ; 
 int /*<<< orphan*/  p_localtime_r (scalar_t__*,struct tm*) ; 

__attribute__((used)) static git_time_t update_tm(struct tm *tm, struct tm *now, unsigned long sec)
{
	time_t n;

	if (tm->tm_mday < 0)
		tm->tm_mday = now->tm_mday;
	if (tm->tm_mon < 0)
		tm->tm_mon = now->tm_mon;
	if (tm->tm_year < 0) {
		tm->tm_year = now->tm_year;
		if (tm->tm_mon > now->tm_mon)
			tm->tm_year--;
	}

	n = mktime(tm) - sec;
	p_localtime_r(&n, tm);
	return n;
}