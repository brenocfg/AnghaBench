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
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
struct iovec {scalar_t__ iov_len; char* iov_base; } ;
typedef  int ssize_t ;
typedef  int f ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  EWOULDBLOCK ; 
 int IOV_MAX ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (struct iovec*,struct iovec const*,size_t) ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int) ; 
 ssize_t readv (int,struct iovec const*,int) ; 

size_t
atomiciov6(ssize_t (*f) (int, const struct iovec *, int), int fd,
    const struct iovec *_iov, int iovcnt,
    int (*cb)(void *, size_t), void *cb_arg)
{
	size_t pos = 0, rem;
	ssize_t res;
	struct iovec iov_array[IOV_MAX], *iov = iov_array;
	struct pollfd pfd;

	if (iovcnt < 0 || iovcnt > IOV_MAX) {
		errno = EINVAL;
		return 0;
	}
	/* Make a copy of the iov array because we may modify it below */
	memcpy(iov, _iov, (size_t)iovcnt * sizeof(*_iov));

#ifndef BROKEN_READV_COMPARISON
	pfd.fd = fd;
	pfd.events = f == readv ? POLLIN : POLLOUT;
#endif
	for (; iovcnt > 0 && iov[0].iov_len > 0;) {
		res = (f) (fd, iov, iovcnt);
		switch (res) {
		case -1:
			if (errno == EINTR)
				continue;
			if (errno == EAGAIN || errno == EWOULDBLOCK) {
#ifndef BROKEN_READV_COMPARISON
				(void)poll(&pfd, 1, -1);
#endif
				continue;
			}
			return 0;
		case 0:
			errno = EPIPE;
			return pos;
		default:
			rem = (size_t)res;
			pos += rem;
			/* skip completed iov entries */
			while (iovcnt > 0 && rem >= iov[0].iov_len) {
				rem -= iov[0].iov_len;
				iov++;
				iovcnt--;
			}
			/* This shouldn't happen... */
			if (rem > 0 && (iovcnt <= 0 || rem > iov[0].iov_len)) {
				errno = EFAULT;
				return 0;
			}
			if (iovcnt == 0)
				break;
			/* update pointer in partially complete iov */
			iov[0].iov_base = ((char *)iov[0].iov_base) + rem;
			iov[0].iov_len -= rem;
		}
		if (cb != NULL && cb(cb_arg, (size_t)res) == -1) {
			errno = EINTR;
			return pos;
		}
	}
	return pos;
}