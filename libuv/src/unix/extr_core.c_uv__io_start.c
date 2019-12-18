#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  nfds; TYPE_2__** watchers; int /*<<< orphan*/  watcher_queue; } ;
typedef  TYPE_1__ uv_loop_t ;
struct TYPE_7__ {int fd; unsigned int pevents; unsigned int events; int /*<<< orphan*/  watcher_queue; } ;
typedef  TYPE_2__ uv__io_t ;

/* Variables and functions */
 int INT_MAX ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 scalar_t__ QUEUE_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QUEUE_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int UV__POLLPRI ; 
 unsigned int UV__POLLRDHUP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  maybe_resize (TYPE_1__*,int) ; 

void uv__io_start(uv_loop_t* loop, uv__io_t* w, unsigned int events) {
  assert(0 == (events & ~(POLLIN | POLLOUT | UV__POLLRDHUP | UV__POLLPRI)));
  assert(0 != events);
  assert(w->fd >= 0);
  assert(w->fd < INT_MAX);

  w->pevents |= events;
  maybe_resize(loop, w->fd + 1);

#if !defined(__sun)
  /* The event ports backend needs to rearm all file descriptors on each and
   * every tick of the event loop but the other backends allow us to
   * short-circuit here if the event mask is unchanged.
   */
  if (w->events == w->pevents)
    return;
#endif

  if (QUEUE_EMPTY(&w->watcher_queue))
    QUEUE_INSERT_TAIL(&loop->watcher_queue, &w->watcher_queue);

  if (loop->watchers[w->fd] == NULL) {
    loop->watchers[w->fd] = w;
    loop->nfds++;
  }
}