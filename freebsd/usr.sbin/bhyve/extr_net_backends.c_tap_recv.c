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
struct net_backend {int fd; } ;
struct iovec {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 scalar_t__ readv (int,struct iovec*,int) ; 

__attribute__((used)) static ssize_t
tap_recv(struct net_backend *be, struct iovec *iov, int iovcnt)
{
	ssize_t ret;

	/* Should never be called without a valid tap fd */
	assert(be->fd != -1);

	ret = readv(be->fd, iov, iovcnt);

	if (ret < 0 && errno == EWOULDBLOCK) {
		return (0);
	}

	return (ret);
}