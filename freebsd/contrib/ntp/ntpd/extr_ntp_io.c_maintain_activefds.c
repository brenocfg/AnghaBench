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
 int /*<<< orphan*/  FD_CLR (int,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int FD_SETSIZE ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  activefds ; 
 int /*<<< orphan*/  exit (int) ; 
 int max (int,int) ; 
 int maxactivefd ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int,int) ; 

void
maintain_activefds(
	int fd,
	int closing
	)
{
	int i;

	if (fd < 0 || fd >= FD_SETSIZE) {
		msyslog(LOG_ERR,
			"Too many sockets in use, FD_SETSIZE %d exceeded by fd %d",
			FD_SETSIZE, fd);
		exit(1);
	}

	if (!closing) {
		FD_SET(fd, &activefds);
		maxactivefd = max(fd, maxactivefd);
	} else {
		FD_CLR(fd, &activefds);
		if (maxactivefd && fd == maxactivefd) {
			for (i = maxactivefd - 1; i >= 0; i--)
				if (FD_ISSET(i, &activefds)) {
					maxactivefd = i;
					break;
				}
			INSIST(fd != maxactivefd);
		}
	}
}