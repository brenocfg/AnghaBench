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
struct wpabuf {int dummy; } ;
struct tm {int tm_wday; int tm_mon; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; scalar_t__ tm_year; int /*<<< orphan*/  tm_mday; } ;

/* Variables and functions */
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,char const*,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void format_date(struct wpabuf *buf)
{
	const char *weekday_str = "Sun\0Mon\0Tue\0Wed\0Thu\0Fri\0Sat";
	const char *month_str = "Jan\0Feb\0Mar\0Apr\0May\0Jun\0"
		"Jul\0Aug\0Sep\0Oct\0Nov\0Dec";
	struct tm *date;
	time_t t;

	t = time(NULL);
	date = gmtime(&t);
	if (date == NULL)
		return;
	wpabuf_printf(buf, "%s, %02d %s %d %02d:%02d:%02d GMT",
		      &weekday_str[date->tm_wday * 4], date->tm_mday,
		      &month_str[date->tm_mon * 4], date->tm_year + 1900,
		      date->tm_hour, date->tm_min, date->tm_sec);
}