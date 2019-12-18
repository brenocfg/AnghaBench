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
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  optval ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 scalar_t__ connect (int,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  set_nonblock (int) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  unset_nonblock (int) ; 
 int waitrfd (int,int*) ; 

__attribute__((used)) static int
timeout_connect(int sockfd, const struct sockaddr *serv_addr,
    socklen_t addrlen, int *timeoutp)
{
	int optval = 0;
	socklen_t optlen = sizeof(optval);

	/* No timeout: just do a blocking connect() */
	if (*timeoutp <= 0)
		return connect(sockfd, serv_addr, addrlen);

	set_nonblock(sockfd);
	if (connect(sockfd, serv_addr, addrlen) == 0) {
		/* Succeeded already? */
		unset_nonblock(sockfd);
		return 0;
	} else if (errno != EINPROGRESS)
		return -1;

	if (waitrfd(sockfd, timeoutp) == -1)
		return -1;

	/* Completed or failed */
	if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &optval, &optlen) == -1) {
		debug("getsockopt: %s", strerror(errno));
		return -1;
	}
	if (optval != 0) {
		errno = optval;
		return -1;
	}
	unset_nonblock(sockfd);
	return 0;
}