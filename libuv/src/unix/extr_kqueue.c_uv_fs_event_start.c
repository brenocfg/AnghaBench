#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int fd; } ;
struct TYPE_8__ {unsigned int cf_flags; TYPE_4__ event_watcher; int /*<<< orphan*/  loop; int /*<<< orphan*/ * path; scalar_t__ realpath_len; int /*<<< orphan*/ * realpath; int /*<<< orphan*/ * cf_cb; int /*<<< orphan*/  cb; } ;
typedef  TYPE_1__ uv_fs_event_t ;
typedef  int /*<<< orphan*/  uv_fs_event_cb ;
struct stat {int st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  POLLIN ; 
 int S_IFDIR ; 
 int UV_EINVAL ; 
 int UV_ENOMEM ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__close_nocheckstdio (int) ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__fs_event ; 
 int uv__fsevents_init (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__handle_start (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__has_forked_with_cfrunloop ; 
 int /*<<< orphan*/  uv__io_init (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uv__io_start (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ uv__is_active (TYPE_1__*) ; 
 int /*<<< orphan*/ * uv__strdup (char const*) ; 

int uv_fs_event_start(uv_fs_event_t* handle,
                      uv_fs_event_cb cb,
                      const char* path,
                      unsigned int flags) {
  int fd;
#if defined(__APPLE__) && MAC_OS_X_VERSION_MAX_ALLOWED >= 1070
  struct stat statbuf;
#endif

  if (uv__is_active(handle))
    return UV_EINVAL;

  handle->cb = cb;
  handle->path = uv__strdup(path);
  if (handle->path == NULL)
    return UV_ENOMEM;

  /* TODO open asynchronously - but how do we report back errors? */
  fd = open(handle->path, O_RDONLY);
  if (fd == -1) {
    uv__free(handle->path);
    handle->path = NULL;
    return UV__ERR(errno);
  }

#if defined(__APPLE__) && MAC_OS_X_VERSION_MAX_ALLOWED >= 1070
  /* Nullify field to perform checks later */
  handle->cf_cb = NULL;
  handle->realpath = NULL;
  handle->realpath_len = 0;
  handle->cf_flags = flags;

  if (fstat(fd, &statbuf))
    goto fallback;
  /* FSEvents works only with directories */
  if (!(statbuf.st_mode & S_IFDIR))
    goto fallback;

  if (!uv__has_forked_with_cfrunloop) {
    int r;
    /* The fallback fd is no longer needed */
    uv__close_nocheckstdio(fd);
    handle->event_watcher.fd = -1;
    r = uv__fsevents_init(handle);
    if (r == 0) {
      uv__handle_start(handle);
    } else {
      uv__free(handle->path);
      handle->path = NULL;
    }
    return r;
  }
fallback:
#endif /* #if defined(__APPLE__) && MAC_OS_X_VERSION_MAX_ALLOWED >= 1070 */

  uv__handle_start(handle);
  uv__io_init(&handle->event_watcher, uv__fs_event, fd);
  uv__io_start(handle->loop, &handle->event_watcher, POLLIN);

  return 0;
}