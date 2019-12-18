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
 int EINVAL ; 
 size_t PKG_MAX_SIZE ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int fd_package_recv (int,int*,unsigned int) ; 

int
fd_recv(int sock, int *fds, size_t nfds)
{
	unsigned int i, step, j;
	int ret, serrno;

	if (nfds == 0 || fds == NULL) {
		errno = EINVAL;
		return (-1);
	}

	ret = i = step = 0;
	while (i < nfds) {
		if (PKG_MAX_SIZE < nfds - i)
			step = PKG_MAX_SIZE;
		else
			step = nfds - i;
		ret = fd_package_recv(sock, fds + i, step);
		if (ret != 0) {
			/* Close all received descriptors. */
			serrno = errno;
			for (j = 0; j < i; j++)
				close(fds[j]);
			errno = serrno;
			break;
		}
		i += step;
	}

	return (ret);
}