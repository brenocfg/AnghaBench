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
typedef  int /*<<< orphan*/  timestamp_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; } ;
struct timeval {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 char* approxidate_alpha (char const*,struct tm*,struct tm*,int*,int*) ; 
 char* approxidate_digit (char const*,struct tm*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ isalpha (unsigned char) ; 
 scalar_t__ isdigit (unsigned char) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  pending_number (struct tm*,int*) ; 
 int /*<<< orphan*/  update_tm (struct tm*,struct tm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static timestamp_t approxidate_str(const char *date,
				   const struct timeval *tv,
				   int *error_ret)
{
	int number = 0;
	int touched = 0;
	struct tm tm, now;
	time_t time_sec;

	time_sec = tv->tv_sec;
	localtime_r(&time_sec, &tm);
	now = tm;

	tm.tm_year = -1;
	tm.tm_mon = -1;
	tm.tm_mday = -1;

	for (;;) {
		unsigned char c = *date;
		if (!c)
			break;
		date++;
		if (isdigit(c)) {
			pending_number(&tm, &number);
			date = approxidate_digit(date-1, &tm, &number, time_sec);
			touched = 1;
			continue;
		}
		if (isalpha(c))
			date = approxidate_alpha(date-1, &tm, &now, &number, &touched);
	}
	pending_number(&tm, &number);
	if (!touched)
		*error_ret = 1;
	return (timestamp_t)update_tm(&tm, &now, 0);
}