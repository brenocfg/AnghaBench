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
struct timezone {int dummy; } ;
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 scalar_t__ DUSECS ; 
 int /*<<< orphan*/  GETTIMEOFDAY (struct timeval*,struct timezone*) ; 
 long HUSECS ; 
 long MAXSTEP ; 
 int MINLOOPS ; 
 long MINSTEP ; 
 int /*<<< orphan*/  TIMEOFDAY ; 
 int /*<<< orphan*/  getclock (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  printf (char*,long,...) ; 

int
default_get_precision(void)
{
	struct timeval tp;
	struct timezone tzp;
#ifdef HAVE_GETCLOCK
	struct timespec ts;
#endif
	long last;
	int i;
	long diff;
	long val;
	long usec;

	usec = 0;
	val = MAXSTEP;
#ifdef HAVE_GETCLOCK
	(void) getclock(TIMEOFDAY, &ts);
	tp.tv_sec = ts.tv_sec;
	tp.tv_usec = ts.tv_nsec / 1000;
#else /*  not HAVE_GETCLOCK */
	GETTIMEOFDAY(&tp, &tzp);
#endif /* not HAVE_GETCLOCK */
	last = tp.tv_usec;
	for (i = 0; i < MINLOOPS && usec < HUSECS;) {
#ifdef HAVE_GETCLOCK
		(void) getclock(TIMEOFDAY, &ts);
		tp.tv_sec = ts.tv_sec;
		tp.tv_usec = ts.tv_nsec / 1000;
#else /*  not HAVE_GETCLOCK */
		GETTIMEOFDAY(&tp, &tzp);
#endif /* not HAVE_GETCLOCK */
		diff = tp.tv_usec - last;
		last = tp.tv_usec;
		if (diff < 0)
		    diff += DUSECS;
		usec += diff;
		if (diff > MINSTEP) {
			i++;
			if (diff < val)
			    val = diff;
		}
	}
	printf("precision  = %ld usec after %d loop%s\n",
	       val, i, (i == 1) ? "" : "s");
	if (usec >= HUSECS) {
		printf("     (Boy this machine is fast ! usec was %ld)\n",
		       usec);
		val = MINSTEP;	/* val <= MINSTEP; fast machine */
	}
	diff = HUSECS;
	for (i = 0; diff > val; i--)
	    diff >>= 1;
	return (i);
}