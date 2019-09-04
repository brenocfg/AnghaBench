#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fd; int priority; int /*<<< orphan*/  work; void* data; } ;
typedef  TYPE_1__ event_t ;
typedef  int /*<<< orphan*/  event_handler_t ;

/* Variables and functions */
 TYPE_1__* Events ; 
 int MAX_EVENTS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int epoll_sethandler (int fd, int prio, event_handler_t handler, void *data) {
  event_t *ev;
  assert (fd >= 0 && fd < MAX_EVENTS);
  ev = Events + fd;
  if (ev->fd != fd) {
    memset (ev, 0, sizeof(event_t));
    ev->fd = fd;
  }
  ev->priority = prio;
  ev->data = data;
  ev->work = handler;
  return 0;
}