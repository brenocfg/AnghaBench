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
typedef  int /*<<< orphan*/  syncmsg ;
struct pollfd {int fd; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRX (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  errno ; 
 int poll (struct pollfd*,int,int) ; 
 int read (int const,int*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int write (int const,int*,int) ; 

__attribute__((used)) static int
synchronize(const int fd, bool waiter)
{
	int syncmsg = 0;
	int r;
	struct pollfd pfd;

	if (waiter) {
		pfd.fd = fd;
		pfd.events = POLLIN;

		/* We use poll to avoid lock up when the peer died unexpectedly */
		r = poll(&pfd, 1, 10000);
		if (r == -1)
			ERRX(EXIT_FAILURE, "poll (%s)", strerror(errno));
		if (r == 0)
			/* Timed out */
			return -1;

		if (read(fd, &syncmsg, sizeof(syncmsg)) == -1)
			ERRX(EXIT_FAILURE, "read (%s)", strerror(errno));
	} else {
		if (write(fd, &syncmsg, sizeof(syncmsg)) == -1)
			ERRX(EXIT_FAILURE, "write (%s)", strerror(errno));
	}

	return 0;
}