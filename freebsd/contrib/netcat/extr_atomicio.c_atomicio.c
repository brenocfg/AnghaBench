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
typedef  int ssize_t ;
typedef  int f ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int) ; 
 ssize_t read (int,void*,size_t) ; 

size_t
atomicio(ssize_t (*f) (int, void *, size_t), int fd, void *_s, size_t n)
{
	char *s = _s;
	size_t pos = 0;
	ssize_t res;
	struct pollfd pfd;

	pfd.fd = fd;
	pfd.events = f == read ? POLLIN : POLLOUT;
	while (n > pos) {
		res = (f) (fd, s + pos, n - pos);
		switch (res) {
		case -1:
			if (errno == EINTR)
				continue;
			if ((errno == EAGAIN) || (errno == ENOBUFS)) {
				(void)poll(&pfd, 1, -1);
				continue;
			}
			return 0;
		case 0:
			errno = EPIPE;
			return pos;
		default:
			pos += (size_t)res;
		}
	}
	return (pos);
}