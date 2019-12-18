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
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int EINTR ; 
 int ETIMEDOUT ; 
 int FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int errno ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int
wait_for_fd(int fd, int timeout)
{
	struct timeval tv;
	fd_set fdset;
	int error, ret;

	error = 0;

	for (;;) {
		FD_ZERO(&fdset);
		FD_SET(fd, &fdset);

		tv.tv_sec = timeout;
		tv.tv_usec = 0;

		ret = select(fd + 1, NULL, &fdset, NULL,
		    timeout == -1 ? NULL : &tv);
		if (ret == 0) {
			error = ETIMEDOUT;
			break;
		} else if (ret == -1) {
			if (errno == EINTR)
				continue;
			error = errno;
			break;
		}
		PJDLOG_ASSERT(ret > 0);
		PJDLOG_ASSERT(FD_ISSET(fd, &fdset));
		break;
	}

	return (error);
}