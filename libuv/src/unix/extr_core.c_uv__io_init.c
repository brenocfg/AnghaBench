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
struct TYPE_3__ {int fd; scalar_t__ wcount; scalar_t__ rcount; scalar_t__ pevents; scalar_t__ events; int /*<<< orphan*/ * cb; int /*<<< orphan*/  watcher_queue; int /*<<< orphan*/  pending_queue; } ;
typedef  TYPE_1__ uv__io_t ;
typedef  int /*<<< orphan*/ * uv__io_cb ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

void uv__io_init(uv__io_t* w, uv__io_cb cb, int fd) {
  assert(cb != NULL);
  assert(fd >= -1);
  QUEUE_INIT(&w->pending_queue);
  QUEUE_INIT(&w->watcher_queue);
  w->cb = cb;
  w->fd = fd;
  w->events = 0;
  w->pevents = 0;

#if defined(UV_HAVE_KQUEUE)
  w->rcount = 0;
  w->wcount = 0;
#endif /* defined(UV_HAVE_KQUEUE) */
}