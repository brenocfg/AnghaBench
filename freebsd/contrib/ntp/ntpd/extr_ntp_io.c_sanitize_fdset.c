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

/* Variables and functions */
 int EBADF ; 
 int EINTR ; 
 int FALSE ; 
 int /*<<< orphan*/  FD_CLR (int,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int TRUE ; 
 int /*<<< orphan*/  activefds ; 
 int /*<<< orphan*/  fdbits (int,int /*<<< orphan*/ *) ; 
 int maxactivefd ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int,...) ; 
 int read (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int/*BOOL*/
sanitize_fdset(
	int	errc
	)
{
	int j, b, maxscan;

#  ifndef HAVE_SIGNALED_IO
	/*
	 * extended FAU debugging output
	 */
	if (errc != EINTR) {
		msyslog(LOG_ERR,
			"select(%d, %s, 0L, 0L, &0.0) error: %m",
			maxactivefd + 1,
			fdbits(maxactivefd, &activefds));
	}
#   endif
	
	if (errc != EBADF)
		return FALSE;

	/* if we have oviously bad FDs, try to sanitize the FD set. */
	for (j = 0, maxscan = 0; j <= maxactivefd; j++) {
		if (FD_ISSET(j, &activefds)) {
			if (-1 != read(j, &b, 0)) {
				maxscan = j;
				continue;
			}
#		    ifndef HAVE_SIGNALED_IO
			msyslog(LOG_ERR,
				"Removing bad file descriptor %d from select set",
				j);
#		    endif
			FD_CLR(j, &activefds);
		}
	}
	if (maxactivefd != maxscan)
		maxactivefd = maxscan;
	return TRUE;
}