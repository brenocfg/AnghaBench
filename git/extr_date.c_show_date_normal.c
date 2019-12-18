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
struct tm {scalar_t__ tm_year; size_t tm_mon; scalar_t__ tm_mday; size_t tm_wday; unsigned int tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * month_names ; 
 int /*<<< orphan*/  show_date_relative (unsigned int,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 unsigned int* weekday_names ; 

__attribute__((used)) static void show_date_normal(struct strbuf *buf, timestamp_t time, struct tm *tm, int tz, struct tm *human_tm, int human_tz, int local)
{
	struct {
		unsigned int	year:1,
				date:1,
				wday:1,
				time:1,
				seconds:1,
				tz:1;
	} hide = { 0 };

	hide.tz = local || tz == human_tz;
	hide.year = tm->tm_year == human_tm->tm_year;
	if (hide.year) {
		if (tm->tm_mon == human_tm->tm_mon) {
			if (tm->tm_mday > human_tm->tm_mday) {
				/* Future date: think timezones */
			} else if (tm->tm_mday == human_tm->tm_mday) {
				hide.date = hide.wday = 1;
			} else if (tm->tm_mday + 5 > human_tm->tm_mday) {
				/* Leave just weekday if it was a few days ago */
				hide.date = 1;
			}
		}
	}

	/* Show "today" times as just relative times */
	if (hide.wday) {
		show_date_relative(time, buf);
		return;
	}

	/*
	 * Always hide seconds for human-readable.
	 * Hide timezone if showing date.
	 * Hide weekday and time if showing year.
	 *
	 * The logic here is two-fold:
	 *  (a) only show details when recent enough to matter
	 *  (b) keep the maximum length "similar", and in check
	 */
	if (human_tm->tm_year) {
		hide.seconds = 1;
		hide.tz |= !hide.date;
		hide.wday = hide.time = !hide.year;
	}

	if (!hide.wday)
		strbuf_addf(buf, "%.3s ", weekday_names[tm->tm_wday]);
	if (!hide.date)
		strbuf_addf(buf, "%.3s %d ", month_names[tm->tm_mon], tm->tm_mday);

	/* Do we want AM/PM depending on locale? */
	if (!hide.time) {
		strbuf_addf(buf, "%02d:%02d", tm->tm_hour, tm->tm_min);
		if (!hide.seconds)
			strbuf_addf(buf, ":%02d", tm->tm_sec);
	} else
		strbuf_rtrim(buf);

	if (!hide.year)
		strbuf_addf(buf, " %d", tm->tm_year + 1900);

	if (!hide.tz)
		strbuf_addf(buf, " %+05d", tz);
}