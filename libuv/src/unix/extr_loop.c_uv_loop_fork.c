#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int nwatchers; int /*<<< orphan*/  watcher_queue; TYPE_2__** watchers; } ;
typedef  TYPE_1__ uv_loop_t ;
struct TYPE_8__ {scalar_t__ pevents; int /*<<< orphan*/  watcher_queue; scalar_t__ events; } ;
typedef  TYPE_2__ uv__io_t ;

/* Variables and functions */
 scalar_t__ QUEUE_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QUEUE_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv__async_fork (TYPE_1__*) ; 
 int uv__io_fork (TYPE_1__*) ; 
 int uv__signal_loop_fork (TYPE_1__*) ; 

int uv_loop_fork(uv_loop_t* loop) {
  int err;
  unsigned int i;
  uv__io_t* w;

  err = uv__io_fork(loop);
  if (err)
    return err;

  err = uv__async_fork(loop);
  if (err)
    return err;

  err = uv__signal_loop_fork(loop);
  if (err)
    return err;

  /* Rearm all the watchers that aren't re-queued by the above. */
  for (i = 0; i < loop->nwatchers; i++) {
    w = loop->watchers[i];
    if (w == NULL)
      continue;

    if (w->pevents != 0 && QUEUE_EMPTY(&w->watcher_queue)) {
      w->events = 0; /* Force re-registration in uv__io_poll. */
      QUEUE_INSERT_TAIL(&loop->watcher_queue, &w->watcher_queue);
    }
  }

  return 0;
}