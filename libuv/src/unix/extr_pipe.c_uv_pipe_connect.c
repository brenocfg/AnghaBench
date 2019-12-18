#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_11__ {int fd; } ;
struct TYPE_9__ {int delayed_error; TYPE_7__ io_watcher; int /*<<< orphan*/  loop; TYPE_2__* connect_req; } ;
typedef  TYPE_1__ uv_pipe_t ;
struct TYPE_10__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  cb; int /*<<< orphan*/ * handle; } ;
typedef  TYPE_2__ uv_connect_t ;
typedef  int /*<<< orphan*/  uv_connect_cb ;
struct sockaddr_un {int /*<<< orphan*/  sun_family; int /*<<< orphan*/  sun_path; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 scalar_t__ EINPROGRESS ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  QUEUE_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  UV_CONNECT ; 
 int UV_EBADF ; 
 int UV_ENOTSOCK ; 
 int UV_HANDLE_READABLE ; 
 int UV_HANDLE_WRITABLE ; 
 int UV__ERR (scalar_t__) ; 
 int connect (int,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uv__io_feed (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  uv__io_start (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__req_init (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int uv__socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv__stream_fd (TYPE_1__*) ; 
 int uv__stream_open (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uv__strscpy (int /*<<< orphan*/ ,char const*,int) ; 

void uv_pipe_connect(uv_connect_t* req,
                    uv_pipe_t* handle,
                    const char* name,
                    uv_connect_cb cb) {
  struct sockaddr_un saddr;
  int new_sock;
  int err;
  int r;

  new_sock = (uv__stream_fd(handle) == -1);

  if (new_sock) {
    err = uv__socket(AF_UNIX, SOCK_STREAM, 0);
    if (err < 0)
      goto out;
    handle->io_watcher.fd = err;
  }

  memset(&saddr, 0, sizeof saddr);
  uv__strscpy(saddr.sun_path, name, sizeof(saddr.sun_path));
  saddr.sun_family = AF_UNIX;

  do {
    r = connect(uv__stream_fd(handle),
                (struct sockaddr*)&saddr, sizeof saddr);
  }
  while (r == -1 && errno == EINTR);

  if (r == -1 && errno != EINPROGRESS) {
    err = UV__ERR(errno);
#if defined(__CYGWIN__) || defined(__MSYS__)
    /* EBADF is supposed to mean that the socket fd is bad, but
       Cygwin reports EBADF instead of ENOTSOCK when the file is
       not a socket.  We do not expect to see a bad fd here
       (e.g. due to new_sock), so translate the error.  */
    if (err == UV_EBADF)
      err = UV_ENOTSOCK;
#endif
    goto out;
  }

  err = 0;
  if (new_sock) {
    err = uv__stream_open((uv_stream_t*)handle,
                          uv__stream_fd(handle),
                          UV_HANDLE_READABLE | UV_HANDLE_WRITABLE);
  }

  if (err == 0)
    uv__io_start(handle->loop, &handle->io_watcher, POLLOUT);

out:
  handle->delayed_error = err;
  handle->connect_req = req;

  uv__req_init(handle->loop, req, UV_CONNECT);
  req->handle = (uv_stream_t*)handle;
  req->cb = cb;
  QUEUE_INIT(&req->queue);

  /* Force callback to run on next tick in case of error. */
  if (err)
    uv__io_feed(handle->loop, &handle->io_watcher);

}