#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zt ;
struct TYPE_4__ {int /*<<< orphan*/  event_watcher; int /*<<< orphan*/  loop; int /*<<< orphan*/ * dir_filename; int /*<<< orphan*/  cb; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ uv_fs_event_t ;
typedef  int /*<<< orphan*/  uv_fs_event_cb ;
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  readlink_cwd ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  cwd ;
typedef  int /*<<< orphan*/  absolute_path ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  POLLIN ; 
 int UV_ENOENT ; 
 int UV_ENOSYS ; 
 scalar_t__ errno ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  memset (struct timeval*,int /*<<< orphan*/ ,int) ; 
 int readlink (char*,char*,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  uv__ahafs_event ; 
 int /*<<< orphan*/  uv__handle_start (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__io_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uv__io_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv__is_ahafs_mounted () ; 
 int uv__setup_ahafs (char const*,int*) ; 
 int /*<<< orphan*/  uv__strdup (char const*) ; 
 int /*<<< orphan*/  uv__strscpy (char*,char const*,int) ; 

int uv_fs_event_start(uv_fs_event_t* handle,
                      uv_fs_event_cb cb,
                      const char* filename,
                      unsigned int flags) {
#ifdef HAVE_SYS_AHAFS_EVPRODS_H
  int  fd, rc, str_offset = 0;
  char cwd[PATH_MAX];
  char absolute_path[PATH_MAX];
  char readlink_cwd[PATH_MAX];
  struct timeval zt;
  fd_set pollfd;


  /* Figure out whether filename is absolute or not */
  if (filename[0] == '\0') {
    /* Missing a pathname */
    return UV_ENOENT;
  }
  else if (filename[0] == '/') {
    /* We have absolute pathname */
    /* TODO(bnoordhuis) Check uv__strscpy() return value. */
    uv__strscpy(absolute_path, filename, sizeof(absolute_path));
  } else {
    /* We have a relative pathname, compose the absolute pathname */
    snprintf(cwd, sizeof(cwd), "/proc/%lu/cwd", (unsigned long) getpid());
    rc = readlink(cwd, readlink_cwd, sizeof(readlink_cwd) - 1);
    if (rc < 0)
      return rc;
    /* readlink does not null terminate our string */
    readlink_cwd[rc] = '\0';

    if (filename[0] == '.' && filename[1] == '/')
      str_offset = 2;

    snprintf(absolute_path, sizeof(absolute_path), "%s%s", readlink_cwd,
             filename + str_offset);
  }

  if (uv__is_ahafs_mounted() < 0)  /* /aha checks failed */
    return UV_ENOSYS;

  /* Setup ahafs */
  rc = uv__setup_ahafs((const char *)absolute_path, &fd);
  if (rc != 0)
    return rc;

  /* Setup/Initialize all the libuv routines */
  uv__handle_start(handle);
  uv__io_init(&handle->event_watcher, uv__ahafs_event, fd);
  handle->path = uv__strdup(filename);
  handle->cb = cb;
  handle->dir_filename = NULL;

  uv__io_start(handle->loop, &handle->event_watcher, POLLIN);

  /* AHAFS wants someone to poll for it to start mointoring.
   *  so kick-start it so that we don't miss an event in the
   *  eventuality of an event that occurs in the current loop. */
  do {
    memset(&zt, 0, sizeof(zt));
    FD_ZERO(&pollfd);
    FD_SET(fd, &pollfd);
    rc = select(fd + 1, &pollfd, NULL, NULL, &zt);
  } while (rc == -1 && errno == EINTR);
  return 0;
#else
  return UV_ENOSYS;
#endif
}