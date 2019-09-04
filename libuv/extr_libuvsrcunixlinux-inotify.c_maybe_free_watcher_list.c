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
struct TYPE_3__ {int /*<<< orphan*/  inotify_fd; int /*<<< orphan*/  inotify_watchers; } ;
typedef  TYPE_1__ uv_loop_t ;
struct watcher_list {int /*<<< orphan*/  wd; int /*<<< orphan*/  watchers; int /*<<< orphan*/  iterating; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST (int /*<<< orphan*/ *) ; 
 scalar_t__ QUEUE_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct watcher_list*) ; 
 int /*<<< orphan*/  uv__free (struct watcher_list*) ; 
 int /*<<< orphan*/  uv__inotify_rm_watch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watcher_root ; 

__attribute__((used)) static void maybe_free_watcher_list(struct watcher_list* w, uv_loop_t* loop) {
  /* if the watcher_list->watchers is being iterated over, we can't free it. */
  if ((!w->iterating) && QUEUE_EMPTY(&w->watchers)) {
    /* No watchers left for this path. Clean up. */
    RB_REMOVE(watcher_root, CAST(&loop->inotify_watchers), w);
    uv__inotify_rm_watch(loop->inotify_fd, w->wd);
    uv__free(w);
  }
}