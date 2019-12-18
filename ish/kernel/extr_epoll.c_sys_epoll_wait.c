#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timespec {int tv_sec; int tv_nsec; } ;
struct TYPE_2__ {int /*<<< orphan*/  poll; } ;
struct fd {TYPE_1__ epollfd; int /*<<< orphan*/ * ops; } ;
struct epoll_event_ {int dummy; } ;
struct epoll_context {int max_events; int /*<<< orphan*/  n; struct epoll_event_* events; } ;
typedef  int int_t ;
typedef  int /*<<< orphan*/  fd_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int _EBADF ; 
 int _EFAULT ; 
 int _EINVAL ; 
 int /*<<< orphan*/  epoll_callback ; 
 int /*<<< orphan*/  epoll_ops ; 
 struct fd* f_get (int /*<<< orphan*/ ) ; 
 int poll_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct epoll_context*,struct timespec*) ; 
 scalar_t__ user_write (int /*<<< orphan*/ ,struct epoll_event_*,int) ; 

int_t sys_epoll_wait(fd_t epoll_f, addr_t events_addr, int_t max_events, int_t timeout) {
    STRACE("epoll_wait(%d, %#x, %d, %d)", epoll_f, events_addr, max_events, timeout);
    struct fd *epoll = f_get(epoll_f);
    if (epoll == NULL)
        return _EBADF;
    if (epoll->ops != &epoll_ops)
        return _EINVAL;

    struct timespec timeout_ts;
    if (timeout != -1) {
        timeout_ts.tv_sec = timeout / 1000;
        timeout_ts.tv_nsec = (timeout % 1000) * 1000000;
    }
    if (max_events <= 0)
        return _EINVAL;
    struct epoll_event_ events[max_events];

    struct epoll_context context = {.events = events, .n = 0, .max_events = max_events};
    int res = poll_wait(epoll->epollfd.poll, epoll_callback, &context, timeout == -1 ? NULL : &timeout_ts);
    if (res >= 0)
        if (user_write(events_addr, events, sizeof(struct epoll_event_) * res))
            return _EFAULT;
    return res;
}