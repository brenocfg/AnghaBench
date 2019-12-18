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
typedef  int uint64_t ;

/* Variables and functions */
 int CASPER_SERVICE_FD ; 
 int CASPER_SERVICE_STDIO ; 
 int STDERR_FILENO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closefrom (int) ; 
 int /*<<< orphan*/  stdnull () ; 

__attribute__((used)) static void
service_clean(int sock, int procfd, uint64_t flags)
{
	int fd, maxfd, minfd;

	assert(sock > STDERR_FILENO);
	assert(procfd > STDERR_FILENO);
	assert(sock != procfd);

	if ((flags & CASPER_SERVICE_STDIO) == 0)
		stdnull();

	if ((flags & CASPER_SERVICE_FD) == 0) {
		if (procfd > sock) {
			maxfd = procfd;
			minfd = sock;
		} else {
			maxfd = sock;
			minfd = procfd;
		}

		for (fd = STDERR_FILENO + 1; fd < maxfd; fd++) {
			if (fd != minfd)
				close(fd);
		}
		closefrom(maxfd + 1);
	}
}