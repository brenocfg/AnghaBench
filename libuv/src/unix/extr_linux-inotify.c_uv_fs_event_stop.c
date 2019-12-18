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
struct TYPE_5__ {int wd; int /*<<< orphan*/  loop; int /*<<< orphan*/  watchers; int /*<<< orphan*/ * path; } ;
typedef  TYPE_1__ uv_fs_event_t ;
struct watcher_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_REMOVE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct watcher_list* find_watcher (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  maybe_free_watcher_list (struct watcher_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__handle_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__is_active (TYPE_1__*) ; 

int uv_fs_event_stop(uv_fs_event_t* handle) {
  struct watcher_list* w;

  if (!uv__is_active(handle))
    return 0;

  w = find_watcher(handle->loop, handle->wd);
  assert(w != NULL);

  handle->wd = -1;
  handle->path = NULL;
  uv__handle_stop(handle);
  QUEUE_REMOVE(&handle->watchers);

  maybe_free_watcher_list(w, handle->loop);

  return 0;
}