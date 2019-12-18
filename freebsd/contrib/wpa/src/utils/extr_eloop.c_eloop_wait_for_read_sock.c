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
struct kevent {int dummy; } ;
typedef  int /*<<< orphan*/  pfd ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int EV_ADD ; 
 int EV_ONESHOT ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  kevent (int,struct kevent*,int,struct kevent*,int,int /*<<< orphan*/ *) ; 
 int kqueue () ; 
 int /*<<< orphan*/  os_memset (struct pollfd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void eloop_wait_for_read_sock(int sock)
{
#ifdef CONFIG_ELOOP_POLL
	struct pollfd pfd;

	if (sock < 0)
		return;

	os_memset(&pfd, 0, sizeof(pfd));
	pfd.fd = sock;
	pfd.events = POLLIN;

	poll(&pfd, 1, -1);
#endif /* CONFIG_ELOOP_POLL */
#if defined(CONFIG_ELOOP_SELECT) || defined(CONFIG_ELOOP_EPOLL)
	/*
	 * We can use epoll() here. But epoll() requres 4 system calls.
	 * epoll_create1(), epoll_ctl() for ADD, epoll_wait, and close() for
	 * epoll fd. So select() is better for performance here.
	 */
	fd_set rfds;

	if (sock < 0)
		return;

	FD_ZERO(&rfds);
	FD_SET(sock, &rfds);
	select(sock + 1, &rfds, NULL, NULL, NULL);
#endif /* defined(CONFIG_ELOOP_SELECT) || defined(CONFIG_ELOOP_EPOLL) */
#ifdef CONFIG_ELOOP_KQUEUE
	int kfd;
	struct kevent ke1, ke2;

	kfd = kqueue();
	if (kfd == -1)
		return;
	EV_SET(&ke1, sock, EVFILT_READ, EV_ADD | EV_ONESHOT, 0, 0, 0);
	kevent(kfd, &ke1, 1, &ke2, 1, NULL);
	close(kfd);
#endif /* CONFIG_ELOOP_KQUEUE */
}