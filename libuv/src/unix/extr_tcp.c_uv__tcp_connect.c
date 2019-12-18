#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; int delayed_error; int /*<<< orphan*/  io_watcher; int /*<<< orphan*/  loop; TYPE_2__* connect_req; } ;
typedef  TYPE_1__ uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_9__ {int /*<<< orphan*/  queue; int /*<<< orphan*/ * handle; int /*<<< orphan*/  cb; } ;
typedef  TYPE_2__ uv_connect_t ;
typedef  int /*<<< orphan*/  uv_connect_cb ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;

/* Variables and functions */
 scalar_t__ ECONNREFUSED ; 
 scalar_t__ EINPROGRESS ; 
 scalar_t__ EINTR ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  QUEUE_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UV_CONNECT ; 
 int UV_EALREADY ; 
 int UV_HANDLE_READABLE ; 
 int UV_HANDLE_WRITABLE ; 
 scalar_t__ UV_TCP ; 
 int UV__ERR (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int connect (int /*<<< orphan*/ ,struct sockaddr const*,unsigned int) ; 
 scalar_t__ errno ; 
 int maybe_new_socket (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uv__io_feed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__io_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__req_init (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__stream_fd (TYPE_1__*) ; 

int uv__tcp_connect(uv_connect_t* req,
                    uv_tcp_t* handle,
                    const struct sockaddr* addr,
                    unsigned int addrlen,
                    uv_connect_cb cb) {
  int err;
  int r;

  assert(handle->type == UV_TCP);

  if (handle->connect_req != NULL)
    return UV_EALREADY;  /* FIXME(bnoordhuis) UV_EINVAL or maybe UV_EBUSY. */

  err = maybe_new_socket(handle,
                         addr->sa_family,
                         UV_HANDLE_READABLE | UV_HANDLE_WRITABLE);
  if (err)
    return err;

  handle->delayed_error = 0;

  do {
    errno = 0;
    r = connect(uv__stream_fd(handle), addr, addrlen);
  } while (r == -1 && errno == EINTR);

  /* We not only check the return value, but also check the errno != 0.
   * Because in rare cases connect() will return -1 but the errno
   * is 0 (for example, on Android 4.3, OnePlus phone A0001_12_150227)
   * and actually the tcp three-way handshake is completed.
   */
  if (r == -1 && errno != 0) {
    if (errno == EINPROGRESS)
      ; /* not an error */
    else if (errno == ECONNREFUSED
#if defined(__OpenBSD__)
      || errno == EINVAL
#endif
      )
    /* If we get ECONNREFUSED (Solaris) or EINVAL (OpenBSD) wait until the
     * next tick to report the error. Solaris and OpenBSD wants to report
     * immediately -- other unixes want to wait.
     */
      handle->delayed_error = UV__ERR(ECONNREFUSED);
    else
      return UV__ERR(errno);
  }

  uv__req_init(handle->loop, req, UV_CONNECT);
  req->cb = cb;
  req->handle = (uv_stream_t*) handle;
  QUEUE_INIT(&req->queue);
  handle->connect_req = req;

  uv__io_start(handle->loop, &handle->io_watcher, POLLOUT);

  if (handle->delayed_error)
    uv__io_feed(handle->loop, &handle->io_watcher);

  return 0;
}