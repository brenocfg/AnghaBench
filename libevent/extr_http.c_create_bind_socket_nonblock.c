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
struct evutil_addrinfo {scalar_t__ ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  on ;
typedef  int evutil_socket_t ;
typedef  int /*<<< orphan*/  ev_socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EVUTIL_SET_SOCKET_ERROR (int) ; 
 int EVUTIL_SOCKET_ERROR () ; 
 int EVUTIL_SOCK_CLOEXEC ; 
 int EVUTIL_SOCK_NONBLOCK ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_sock_warn (int,char*) ; 
 int /*<<< orphan*/  evutil_closesocket (int) ; 
 scalar_t__ evutil_make_listen_socket_reuseable (int) ; 
 int evutil_socket_ (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static evutil_socket_t
create_bind_socket_nonblock(struct evutil_addrinfo *ai, int reuse)
{
	evutil_socket_t fd;

	int on = 1, r;
	int serrno;

	/* Create listen socket */
	fd = evutil_socket_(ai ? ai->ai_family : AF_INET,
	    SOCK_STREAM|EVUTIL_SOCK_NONBLOCK|EVUTIL_SOCK_CLOEXEC, 0);
	if (fd == -1) {
			event_sock_warn(-1, "socket");
			return (-1);
	}

	if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void *)&on, sizeof(on))<0)
		goto out;
	if (reuse) {
		if (evutil_make_listen_socket_reuseable(fd) < 0)
			goto out;
	}

	if (ai != NULL) {
		r = bind(fd, ai->ai_addr, (ev_socklen_t)ai->ai_addrlen);
		if (r == -1)
			goto out;
	}

	return (fd);

 out:
	serrno = EVUTIL_SOCKET_ERROR();
	evutil_closesocket(fd);
	EVUTIL_SET_SOCKET_ERROR(serrno);
	return (-1);
}