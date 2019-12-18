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
typedef  char wchar_t ;
typedef  int time_t ;
struct tm {scalar_t__ tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 struct tm* localtime (int*) ; 
 scalar_t__ use_ampm ; 
 int /*<<< orphan*/  wcsftime (char*,int,char const*,struct tm*) ; 
 int wcslen (char*) ; 
 int wcswidth (char*,int) ; 
 int /*<<< orphan*/  xo_attr (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  xo_emit (char*,char*,...) ; 

int
pr_attime(time_t *started, time_t *now)
{
	static wchar_t buf[256];
	struct tm tp, tm;
	time_t diff;
	const wchar_t *fmt;
	int len, width, offset = 0;

	tp = *localtime(started);
	tm = *localtime(now);
	diff = *now - *started;

	/* If more than a week, use day-month-year. */
	if (diff > 86400 * 7)
		fmt = L"%d%b%y";

	/* If not today, use day-hour-am/pm. */
	else if (tm.tm_mday != tp.tm_mday ||
		 tm.tm_mon != tp.tm_mon ||
		 tm.tm_year != tp.tm_year) {
	/* The line below does not take DST into consideration */
	/* else if (*now / 86400 != *started / 86400) { */
		fmt = use_ampm ? L"%a%I%p" : L"%a%H";
	}

	/* Default is hh:mm{am,pm}. */
	else {
		fmt = use_ampm ? L"%l:%M%p" : L"%k:%M";
	}

	(void)wcsftime(buf, sizeof(buf), fmt, &tp);
	len = wcslen(buf);
	width = wcswidth(buf, len);
	xo_attr("since", "%lu", (unsigned long) *started);
	xo_attr("delta", "%lu", (unsigned long) diff);
	if (len == width)
		xo_emit("{:login-time/%-7.7ls/%ls}", buf);
	else if (width < 7)
	        xo_emit("{:login-time/%ls}%.*s", buf, 7 - width, "      ");
	else {
		xo_emit("{:login-time/%ls}", buf);
		offset = width - 7;
	}
	return (offset);
}