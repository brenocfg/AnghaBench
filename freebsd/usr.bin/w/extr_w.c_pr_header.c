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
typedef  int time_t ;
struct timespec {int tv_sec; } ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_UPTIME ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int getloadavg (double*,scalar_t__) ; 
 int /*<<< orphan*/  localtime (int*) ; 
 scalar_t__ nitems (double*) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 scalar_t__ sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int,...) ; 
 scalar_t__ strftime (char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ use_ampm ; 
 scalar_t__ use_comma ; 
 int /*<<< orphan*/  xo_emit (char const*,...) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 

__attribute__((used)) static void
pr_header(time_t *nowp, int nusers)
{
	double avenrun[3];
	time_t uptime;
	struct timespec tp;
	int days, hrs, i, mins, secs;
	char buf[256];
	struct sbuf *upbuf;

	upbuf = sbuf_new_auto();
	/*
	 * Print time of day.
	 */
	if (strftime(buf, sizeof(buf),
	    use_ampm ? "%l:%M%p" : "%k:%M", localtime(nowp)) != 0)
		xo_emit("{:time-of-day/%s} ", buf);
	/*
	 * Print how long system has been up.
	 */
	if (clock_gettime(CLOCK_UPTIME, &tp) != -1) {
		uptime = tp.tv_sec;
		if (uptime > 60)
			uptime += 30;
		days = uptime / 86400;
		uptime %= 86400;
		hrs = uptime / 3600;
		uptime %= 3600;
		mins = uptime / 60;
		secs = uptime % 60;
		xo_emit(" up");
		xo_emit("{e:uptime/%lu}", (unsigned long) tp.tv_sec);
		xo_emit("{e:days/%d}{e:hours/%d}{e:minutes/%d}{e:seconds/%d}", days, hrs, mins, secs);

		if (days > 0)
			sbuf_printf(upbuf, " %d day%s,",
				days, days > 1 ? "s" : "");
		if (hrs > 0 && mins > 0)
			sbuf_printf(upbuf, " %2d:%02d,", hrs, mins);
		else if (hrs > 0)
			sbuf_printf(upbuf, " %d hr%s,",
				hrs, hrs > 1 ? "s" : "");
		else if (mins > 0)
			sbuf_printf(upbuf, " %d min%s,",
				mins, mins > 1 ? "s" : "");
		else 
			sbuf_printf(upbuf, " %d sec%s,",
				secs, secs > 1 ? "s" : "");
		if (sbuf_finish(upbuf) != 0)
			xo_err(1, "Could not generate output");
		xo_emit("{:uptime-human/%s}", sbuf_data(upbuf));
		sbuf_delete(upbuf);
	}

	/* Print number of users logged in to system */
	xo_emit(" {:users/%d} {Np:user,users}", nusers);

	/*
	 * Print 1, 5, and 15 minute load averages.
	 */
	if (getloadavg(avenrun, nitems(avenrun)) == -1)
		xo_emit(", no load average information available\n");
	else {
	        static const char *format[] = {
		    " {:load-average-1/%.2f}",
		    " {:load-average-5/%.2f}",
		    " {:load-average-15/%.2f}",
		};
		xo_emit(", load averages:");
		for (i = 0; i < (int)(nitems(avenrun)); i++) {
			if (use_comma && i > 0)
				xo_emit(",");
			xo_emit(format[i], avenrun[i]);
		}
		xo_emit("\n");
	}
}