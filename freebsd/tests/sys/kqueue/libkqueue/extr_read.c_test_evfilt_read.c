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
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqfd ; 
 int /*<<< orphan*/  kqueue () ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sockfd ; 
 int /*<<< orphan*/  test_kevent_socket_add () ; 
 int /*<<< orphan*/  test_kevent_socket_clear () ; 
 int /*<<< orphan*/  test_kevent_socket_del () ; 
 int /*<<< orphan*/  test_kevent_socket_disable_and_enable () ; 
 int /*<<< orphan*/  test_kevent_socket_dispatch () ; 
 int /*<<< orphan*/  test_kevent_socket_eof () ; 
 int /*<<< orphan*/  test_kevent_socket_get () ; 
 int /*<<< orphan*/  test_kevent_socket_oneshot () ; 

void
test_evfilt_read()
{
    /* Create a connected pair of full-duplex sockets for testing socket events */
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockfd) < 0) 
        abort();

    kqfd = kqueue();
    test_kevent_socket_add();
    test_kevent_socket_del();
    test_kevent_socket_get();
    test_kevent_socket_disable_and_enable();
    test_kevent_socket_oneshot();
    test_kevent_socket_clear();
#if HAVE_EV_DISPATCH
    test_kevent_socket_dispatch();
#endif
    test_kevent_socket_eof();
    close(kqfd);
}