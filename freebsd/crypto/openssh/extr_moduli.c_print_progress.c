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

/* Variables and functions */
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/  ctime (scalar_t__*) ; 
 int /*<<< orphan*/  fmt_time (scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  logit (char*,int /*<<< orphan*/ ,unsigned long,unsigned long,...) ; 
 scalar_t__ monotime () ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_progress(unsigned long start_lineno, unsigned long current_lineno,
    unsigned long end_lineno)
{
	static time_t time_start, time_prev;
	time_t time_now, elapsed;
	unsigned long num_to_process, processed, remaining, percent, eta;
	double time_per_line;
	char *eta_str;

	time_now = monotime();
	if (time_start == 0) {
		time_start = time_prev = time_now;
		return;
	}
	/* print progress after 1m then once per 5m */
	if (time_now - time_prev < 5 * 60)
		return;
	time_prev = time_now;
	elapsed = time_now - time_start;
	processed = current_lineno - start_lineno;
	remaining = end_lineno - current_lineno;
	num_to_process = end_lineno - start_lineno;
	time_per_line = (double)elapsed / processed;
	/* if we don't know how many we're processing just report count+time */
	time(&time_now);
	if (end_lineno == ULONG_MAX) {
		logit("%.24s processed %lu in %s", ctime(&time_now),
		    processed, fmt_time(elapsed));
		return;
	}
	percent = 100 * processed / num_to_process;
	eta = time_per_line * remaining;
	eta_str = xstrdup(fmt_time(eta));
	logit("%.24s processed %lu of %lu (%lu%%) in %s, ETA %s",
	    ctime(&time_now), processed, num_to_process, percent,
	    fmt_time(elapsed), eta_str);
	free(eta_str);
}