#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fd; } ;
struct TYPE_6__ {char const* pipe_fname; TYPE_1__ io_watcher; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ uv_pipe_t ;
struct sockaddr_un {int /*<<< orphan*/  sun_family; int /*<<< orphan*/  sun_path; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int UV_EACCES ; 
 int UV_EINVAL ; 
 int UV_ENOENT ; 
 int UV_ENOMEM ; 
 int /*<<< orphan*/  UV_HANDLE_BOUND ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int /*<<< orphan*/  uv__free (void*) ; 
 int uv__socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* uv__strdup (char const*) ; 
 scalar_t__ uv__stream_fd (TYPE_2__*) ; 
 int /*<<< orphan*/  uv__strscpy (int /*<<< orphan*/ ,char const*,int) ; 

int uv_pipe_bind(uv_pipe_t* handle, const char* name) {
  struct sockaddr_un saddr;
  const char* pipe_fname;
  int sockfd;
  int err;

  pipe_fname = NULL;

  /* Already bound? */
  if (uv__stream_fd(handle) >= 0)
    return UV_EINVAL;

  /* Make a copy of the file name, it outlives this function's scope. */
  pipe_fname = uv__strdup(name);
  if (pipe_fname == NULL)
    return UV_ENOMEM;

  /* We've got a copy, don't touch the original any more. */
  name = NULL;

  err = uv__socket(AF_UNIX, SOCK_STREAM, 0);
  if (err < 0)
    goto err_socket;
  sockfd = err;

  memset(&saddr, 0, sizeof saddr);
  uv__strscpy(saddr.sun_path, pipe_fname, sizeof(saddr.sun_path));
  saddr.sun_family = AF_UNIX;

  if (bind(sockfd, (struct sockaddr*)&saddr, sizeof saddr)) {
    err = UV__ERR(errno);
    /* Convert ENOENT to EACCES for compatibility with Windows. */
    if (err == UV_ENOENT)
      err = UV_EACCES;

    uv__close(sockfd);
    goto err_socket;
  }

  /* Success. */
  handle->flags |= UV_HANDLE_BOUND;
  handle->pipe_fname = pipe_fname; /* Is a strdup'ed copy. */
  handle->io_watcher.fd = sockfd;
  return 0;

err_socket:
  uv__free((void*)pipe_fname);
  return err;
}