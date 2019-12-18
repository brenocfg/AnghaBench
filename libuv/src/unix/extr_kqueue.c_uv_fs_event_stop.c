#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fd; } ;
struct TYPE_7__ {int /*<<< orphan*/ * path; TYPE_4__ event_watcher; int /*<<< orphan*/  loop; int /*<<< orphan*/ * cf_cb; } ;
typedef  TYPE_1__ uv_fs_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv__close (int) ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int uv__fsevents_close (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__handle_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__has_forked_with_cfrunloop ; 
 int /*<<< orphan*/  uv__io_close (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  uv__is_active (TYPE_1__*) ; 

int uv_fs_event_stop(uv_fs_event_t* handle) {
  int r;
  r = 0;

  if (!uv__is_active(handle))
    return 0;

  uv__handle_stop(handle);

#if defined(__APPLE__) && MAC_OS_X_VERSION_MAX_ALLOWED >= 1070
  if (!uv__has_forked_with_cfrunloop && handle->cf_cb != NULL)
    r = uv__fsevents_close(handle);
#endif

  if (handle->event_watcher.fd != -1) {
    uv__io_close(handle->loop, &handle->event_watcher);
    uv__close(handle->event_watcher.fd);
    handle->event_watcher.fd = -1;
  }

  uv__free(handle->path);
  handle->path = NULL;

  return r;
}