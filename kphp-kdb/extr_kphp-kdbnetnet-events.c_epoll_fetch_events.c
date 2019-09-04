#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fd; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  epoll_ready; int /*<<< orphan*/  ready; } ;
typedef  TYPE_2__ event_t ;
struct TYPE_7__ {int fd; } ;
struct TYPE_9__ {int /*<<< orphan*/  events; TYPE_1__ data; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 TYPE_2__* Events ; 
 int MAX_EVENTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  epoll_fd ; 
 int /*<<< orphan*/  epoll_unconv_flags (int /*<<< orphan*/ ) ; 
 int epoll_wait (int /*<<< orphan*/ ,TYPE_4__*,int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  ev_timestamp ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* new_ev_list ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  put_event_into_heap (TYPE_2__*) ; 
 int verbosity ; 

int epoll_fetch_events (int timeout) {
  int fd, i;
  int res = epoll_wait (epoll_fd, new_ev_list, MAX_EVENTS, timeout);
  if (res < 0 && errno == EINTR) {
    res = 0;
  }
  if (res < 0) {
    perror ("epoll_wait()");
  }
  if (verbosity > 1 && res) {
    kprintf ("epoll_wait(%d, ...) = %d\n", epoll_fd, res);
  }
  for (i = 0; i < res; i++) {
    fd = new_ev_list[i].data.fd;
    assert (fd >= 0 && fd < MAX_EVENTS);
    event_t *ev = Events + fd;
    assert (ev->fd == fd);
    ev->ready |= epoll_unconv_flags (ev->epoll_ready = new_ev_list[i].events);
    ev->timestamp = ev_timestamp;
    put_event_into_heap (ev);
  }
  return res;
}