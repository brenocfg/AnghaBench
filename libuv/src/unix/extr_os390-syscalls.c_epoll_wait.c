#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; struct pollfd* items; } ;
typedef  TYPE_1__ uv__os390_epoll ;
struct pollfd {int fd; int revents; } ;
struct epoll_event {int fd; int events; } ;
typedef  int /*<<< orphan*/  nmsgsfds_t ;

/* Variables and functions */
 int POLLIN ; 
 int POLLOUT ; 
 int _NFDS (int) ; 
 int _NMSGS (int) ; 
 int /*<<< orphan*/  _SET_FDS_MSGS (int /*<<< orphan*/ ,int,int) ; 
 int poll (struct pollfd*,int /*<<< orphan*/ ,int) ; 

int epoll_wait(uv__os390_epoll* lst, struct epoll_event* events,
               int maxevents, int timeout) {
  nmsgsfds_t size;
  struct pollfd* pfds;
  int pollret;
  int reventcount;
  int nevents;

  _SET_FDS_MSGS(size, 1, lst->size - 1);
  pfds = lst->items;
  pollret = poll(pfds, size, timeout);
  if (pollret <= 0)
    return pollret;

  pollret = _NFDS(pollret) + _NMSGS(pollret);

  reventcount = 0;
  nevents = 0;
  for (int i = 0; 
       i < lst->size && i < maxevents && reventcount < pollret; ++i) {
    struct epoll_event ev;
    struct pollfd* pfd;

    pfd = &pfds[i];
    if (pfd->fd == -1 || pfd->revents == 0)
      continue;

    ev.fd = pfd->fd;
    ev.events = pfd->revents;
    if (pfd->revents & POLLIN && pfd->revents & POLLOUT)
      reventcount += 2;
    else if (pfd->revents & (POLLIN | POLLOUT))
      ++reventcount;

    pfd->revents = 0;
    events[nevents++] = ev;
  }

  return nevents;
}