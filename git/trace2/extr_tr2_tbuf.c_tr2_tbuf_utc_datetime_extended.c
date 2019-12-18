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
struct tr2_tbuf {int /*<<< orphan*/  buf; } ;
struct tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  xsnprintf (int /*<<< orphan*/ ,int,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

void tr2_tbuf_utc_datetime_extended(struct tr2_tbuf *tb)
{
	struct timeval tv;
	struct tm tm;
	time_t secs;

	gettimeofday(&tv, NULL);
	secs = tv.tv_sec;
	gmtime_r(&secs, &tm);

	xsnprintf(tb->buf, sizeof(tb->buf),
		  "%4d-%02d-%02dT%02d:%02d:%02d.%06ldZ", tm.tm_year + 1900,
		  tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
		  (long)tv.tv_usec);
}