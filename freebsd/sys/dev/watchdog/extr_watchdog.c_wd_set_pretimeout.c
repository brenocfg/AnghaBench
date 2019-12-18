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
typedef  int u_int ;
struct timespec {int tv_sec; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int hz ; 
 int pow2ns_to_ticks (int) ; 
 int /*<<< orphan*/  pow2ns_to_ts (int,struct timespec*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  wd_pretimeo_handle ; 
 int wd_pretimeout ; 
 int /*<<< orphan*/  wd_timeout_cb ; 
 int wdog_kern_last_timeout () ; 

__attribute__((used)) static int
wd_set_pretimeout(int newtimeout, int disableiftoolong)
{
	u_int utime;
	struct timespec utime_ts;
	int timeout_ticks;

	utime = wdog_kern_last_timeout();
	pow2ns_to_ts(utime, &utime_ts);
	/* do not permit a pre-timeout >= than the timeout. */
	if (newtimeout >= utime_ts.tv_sec) {
		/*
		 * If 'disableiftoolong' then just fall through
		 * so as to disable the pre-watchdog
		 */
		if (disableiftoolong)
			newtimeout = 0;
		else
			return EINVAL;
	}

	/* disable the pre-timeout */
	if (newtimeout == 0) {
		wd_pretimeout = 0;
		callout_stop(&wd_pretimeo_handle);
		return 0;
	}

	timeout_ticks = pow2ns_to_ticks(utime) - (hz*newtimeout);
#if 0
	printf("wd_set_pretimeout: "
	    "newtimeout: %d, "
	    "utime: %d -> utime_ticks: %d, "
	    "hz*newtimeout: %d, "
	    "timeout_ticks: %d -> sec: %d\n",
	    newtimeout,
	    utime, pow2ns_to_ticks(utime),
	    hz*newtimeout,
	    timeout_ticks, timeout_ticks / hz);
#endif

	/* We determined the value is sane, so reset the callout */
	(void) callout_reset(&wd_pretimeo_handle,
	    timeout_ticks, wd_timeout_cb, "pre");
	wd_pretimeout = newtimeout;
	return 0;
}