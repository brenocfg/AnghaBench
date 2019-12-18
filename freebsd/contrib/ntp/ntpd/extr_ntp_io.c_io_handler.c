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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  l_fp ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  activefds ; 
 int debug ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  get_systime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handler_calls ; 
 int /*<<< orphan*/  input_handler_scan (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ maxactivefd ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ sanitize_fdset (scalar_t__) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  wait_for_signal () ; 

void
io_handler(void)
{
#  ifndef HAVE_SIGNALED_IO
	fd_set rdfdes;
	int nfound;

	/*
	 * Use select() on all on all input fd's for unlimited
	 * time.  select() will terminate on SIGALARM or on the
	 * reception of input.	Using select() means we can't do
	 * robust signal handling and we get a potential race
	 * between checking for alarms and doing the select().
	 * Mostly harmless, I think.
	 */
	/*
	 * On VMS, I suspect that select() can't be interrupted
	 * by a "signal" either, so I take the easy way out and
	 * have select() time out after one second.
	 * System clock updates really aren't time-critical,
	 * and - lacking a hardware reference clock - I have
	 * yet to learn about anything else that is.
	 */
	++handler_calls;
	rdfdes = activefds;
#   if !defined(VMS) && !defined(SYS_VXWORKS)
	nfound = select(maxactivefd + 1, &rdfdes, NULL,
			NULL, NULL);
#   else	/* VMS, VxWorks */
	/* make select() wake up after one second */
	{
		struct timeval t1;
		t1.tv_sec  = 1;
		t1.tv_usec = 0;
		nfound = select(maxactivefd + 1,
				&rdfdes, NULL, NULL,
				&t1);
	}
#   endif	/* VMS, VxWorks */
	if (nfound < 0 && sanitize_fdset(errno)) {
		struct timeval t1;
		t1.tv_sec  = 0;
		t1.tv_usec = 0;
		rdfdes = activefds;
		nfound = select(maxactivefd + 1,
				&rdfdes, NULL, NULL,
				&t1);
	}

	if (nfound > 0) {
		l_fp ts;

		get_systime(&ts);

		input_handler_scan(&ts, &rdfdes);
	} else if (nfound == -1 && errno != EINTR) {
		msyslog(LOG_ERR, "select() error: %m");
	}
#   ifdef DEBUG
	else if (debug > 4) {
		msyslog(LOG_DEBUG, "select(): nfound=%d, error: %m", nfound);
	} else {
		DPRINTF(3, ("select() returned %d: %m\n", nfound));
	}
#   endif /* DEBUG */
#  else /* HAVE_SIGNALED_IO */
	wait_for_signal();
#  endif /* HAVE_SIGNALED_IO */
}