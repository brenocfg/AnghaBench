#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fd; scalar_t__ in_queue; } ;
typedef  TYPE_1__ event_t ;

/* Variables and functions */
 TYPE_1__* Events ; 
 int MAX_EVENTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  epoll_remove (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remove_event_from_heap (TYPE_1__*,int /*<<< orphan*/ ) ; 

int epoll_close (int fd) {
  event_t *ev;
  assert (fd >= 0 && fd < MAX_EVENTS);
  ev = Events + fd;
  if (ev->fd != fd) {
    return -1;
  }
  epoll_remove (fd);
  if (ev->in_queue) {
    remove_event_from_heap (ev, 0);
  }
  memset (ev, 0, sizeof (event_t));
  ev->fd = -1;
  return 0;
}