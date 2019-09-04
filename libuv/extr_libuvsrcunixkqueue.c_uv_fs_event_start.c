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
struct TYPE_5__ {int /*<<< orphan*/  event_watcher; int /*<<< orphan*/  loop; int /*<<< orphan*/  cb; int /*<<< orphan*/ * path; } ;
typedef  TYPE_1__ uv_fs_event_t ;
typedef  int /*<<< orphan*/  uv_fs_event_cb ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  POLLIN ; 
 int UV_EINVAL ; 
 int UV_ENOMEM ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__close_nocheckstdio (int) ; 
 int /*<<< orphan*/  uv__fs_event ; 
 int /*<<< orphan*/  uv__handle_start (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__io_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uv__io_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv__is_active (TYPE_1__*) ; 
 int /*<<< orphan*/ * uv__strdup (char const*) ; 

int uv_fs_event_start(uv_fs_event_t* handle,
                      uv_fs_event_cb cb,
                      const char* path,
                      unsigned int flags) {
  int fd;

  if (uv__is_active(handle))
    return UV_EINVAL;

#if defined(__APPLE__)
  /* Nullify field to perform checks later */
  handle->cf_cb = NULL;
  handle->realpath = NULL;
  handle->realpath_len = 0;
  handle->cf_flags = flags;

  if (!uv__has_forked_with_cfrunloop) {
    int r;
    /* The fallback fd is not used */
    handle->event_watcher.fd = -1;
    handle->path = uv__strdup(path);
    if (handle->path == NULL)
      return UV_ENOMEM;
    handle->cb = cb;
    r = uv__fsevents_init(handle);
    if (r == 0) {
      uv__handle_start(handle);
    } else {
      uv__free(handle->path);
      handle->path = NULL;
    }
    return r;
  }
#endif /* defined(__APPLE__) */

  /* TODO open asynchronously - but how do we report back errors? */
  fd = open(path, O_RDONLY);
  if (fd == -1)
    return UV__ERR(errno);

  handle->path = uv__strdup(path);
  if (handle->path == NULL) {
    uv__close_nocheckstdio(fd);
    return UV_ENOMEM;
  }

  handle->cb = cb;
  uv__handle_start(handle);
  uv__io_init(&handle->event_watcher, uv__fs_event, fd);
  uv__io_start(handle->loop, &handle->event_watcher, POLLIN);

  return 0;
}