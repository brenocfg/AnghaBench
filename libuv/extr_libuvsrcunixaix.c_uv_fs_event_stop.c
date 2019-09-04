#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uv_fs_event_t ;

/* Variables and functions */
 int UV_ENOSYS ; 

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