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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
struct event_base {int dummy; } ;
typedef  int /*<<< orphan*/  latest ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  TRACE (int,char*) ; 
 int TRUE ; 
 struct timeval add_tval (struct timeval,struct timeval) ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int debug ; 
 int event_base_gettimeofday_cached (struct event_base*,struct timeval*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int labs (long) ; 
 int /*<<< orphan*/  memcmp (struct timeval*,struct timeval*,int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,long,long) ; 
 int /*<<< orphan*/  progname ; 
 struct timeval sub_tval (struct timeval,struct timeval) ; 

int
gettimeofday_cached(
	struct event_base *	b,
	struct timeval *	caller_tv
	)
{
#if defined(_EVENT_HAVE_CLOCK_GETTIME) && defined(CLOCK_MONOTONIC)
	static struct event_base *	cached_b;
	static struct timeval		cached;
	static struct timeval		adj_cached;
	static struct timeval		offset;
	static int			offset_ready;
	struct timeval			latest;
	struct timeval			systemt;
	struct timespec			ts;
	struct timeval			mono;
	struct timeval			diff;
	int				cgt_rc;
	int				gtod_rc;

	event_base_gettimeofday_cached(b, &latest);
	if (b == cached_b &&
	    !memcmp(&latest, &cached, sizeof(latest))) {
		*caller_tv = adj_cached;
		return 0;
	}
	cached = latest;
	cached_b = b;
	if (!offset_ready) {
		cgt_rc = clock_gettime(CLOCK_MONOTONIC, &ts);
		gtod_rc = gettimeofday(&systemt, NULL);
		if (0 != gtod_rc) {
			msyslog(LOG_ERR,
				"%s: gettimeofday() error %m",
				progname);
			exit(1);
		}
		diff = sub_tval(systemt, latest);
		if (debug > 1)
			printf("system minus cached %+ld.%06ld\n",
			       (long)diff.tv_sec, (long)diff.tv_usec);
		if (0 != cgt_rc || labs((long)diff.tv_sec) < 3600) {
			/*
			 * Either use_monotonic == 0, or this libevent
			 * has been repaired.  Leave offset at zero.
			 */
		} else {
			mono.tv_sec = ts.tv_sec;
			mono.tv_usec = ts.tv_nsec / 1000;
			diff = sub_tval(latest, mono);
			if (debug > 1)
				printf("cached minus monotonic %+ld.%06ld\n",
				       (long)diff.tv_sec, (long)diff.tv_usec);
			if (labs((long)diff.tv_sec) < 3600) {
				/* older libevent2 using monotonic */
				offset = sub_tval(systemt, mono);
				TRACE(1, ("%s: Offsetting libevent CLOCK_MONOTONIC times  by %+ld.%06ld\n",
					 "gettimeofday_cached",
					 (long)offset.tv_sec,
					 (long)offset.tv_usec));
			}
		}
		offset_ready = TRUE;
	}
	adj_cached = add_tval(cached, offset);
	*caller_tv = adj_cached;

	return 0;
#else
	return event_base_gettimeofday_cached(b, caller_tv);
#endif
}