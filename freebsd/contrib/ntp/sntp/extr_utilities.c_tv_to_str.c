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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int abs (int) ; 
 int difftime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* emalloc (size_t const) ; 
 int /*<<< orphan*/  gmtime (int /*<<< orphan*/ *) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t const,char*,int,int,int,int,int,int,int,int,int) ; 

char *
tv_to_str(
	const struct timeval *tv
	)
{
	const size_t bufsize = 48;
	char *buf;
	time_t gmt_time, local_time;
	struct tm *p_tm_local;
	int hh, mm, lto;

	/*
	 * convert to struct tm in UTC, then intentionally feed
	 * that tm to mktime() which expects local time input, to
	 * derive the offset from UTC to local time.
	 */
	gmt_time = tv->tv_sec;
	local_time = mktime(gmtime(&gmt_time));
	p_tm_local = localtime(&gmt_time);

	/* Local timezone offsets should never cause an overflow.  Yeah. */
	lto = difftime(local_time, gmt_time);
	lto /= 60;
	hh = lto / 60;
	mm = abs(lto % 60);

	buf = emalloc(bufsize);
	snprintf(buf, bufsize,
		 "%d-%.2d-%.2d %.2d:%.2d:%.2d.%.6d (%+03d%02d)",
		 p_tm_local->tm_year + 1900,
		 p_tm_local->tm_mon + 1,
		 p_tm_local->tm_mday,
		 p_tm_local->tm_hour,
		 p_tm_local->tm_min,
		 p_tm_local->tm_sec,
		 (int)tv->tv_usec,
		 hh,
		 mm);

	return buf;
}