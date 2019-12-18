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
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
typedef  scalar_t__ evutil_socket_t ;

/* Variables and functions */
 scalar_t__ EVUTIL_ERR_CONNECT_REFUSED (int) ; 
 scalar_t__ EVUTIL_ERR_CONNECT_RETRIABLE (int) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ connect (scalar_t__,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  evutil_closesocket (scalar_t__) ; 
 scalar_t__ evutil_make_socket_nonblocking (scalar_t__) ; 
 int evutil_socket_geterror (scalar_t__) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
evutil_socket_connect_(evutil_socket_t *fd_ptr, const struct sockaddr *sa, int socklen)
{
	int made_fd = 0;

	if (*fd_ptr < 0) {
		if ((*fd_ptr = socket(sa->sa_family, SOCK_STREAM, 0)) < 0)
			goto err;
		made_fd = 1;
		if (evutil_make_socket_nonblocking(*fd_ptr) < 0) {
			goto err;
		}
	}

	if (connect(*fd_ptr, sa, socklen) < 0) {
		int e = evutil_socket_geterror(*fd_ptr);
		if (EVUTIL_ERR_CONNECT_RETRIABLE(e))
			return 0;
		if (EVUTIL_ERR_CONNECT_REFUSED(e))
			return 2;
		goto err;
	} else {
		return 1;
	}

err:
	if (made_fd) {
		evutil_closesocket(*fd_ptr);
		*fd_ptr = -1;
	}
	return -1;
}