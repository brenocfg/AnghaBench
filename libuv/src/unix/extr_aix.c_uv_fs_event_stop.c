#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int fd; } ;
struct TYPE_6__ {TYPE_4__ event_watcher; int /*<<< orphan*/ * path; int /*<<< orphan*/ * dir_filename; int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_fs_event_t ;

/* Variables and functions */
 int UV_ENOSYS ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__handle_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__io_close (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  uv__is_active (TYPE_1__*) ; 
 scalar_t__ uv__path_is_a_directory (int /*<<< orphan*/ *) ; 

int uv_fs_event_stop(uv_fs_event_t* handle) {
#ifdef HAVE_SYS_AHAFS_EVPRODS_H
  if (!uv__is_active(handle))
    return 0;

  uv__io_close(handle->loop, &handle->event_watcher);
  uv__handle_stop(handle);

  if (uv__path_is_a_directory(handle->path) == 0) {
    uv__free(handle->dir_filename);
    handle->dir_filename = NULL;
  }

  uv__free(handle->path);
  handle->path = NULL;
  uv__close(handle->event_watcher.fd);
  handle->event_watcher.fd = -1;

  return 0;
#else
  return UV_ENOSYS;
#endif
}