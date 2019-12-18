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
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;
struct TYPE_6__ {scalar_t__ send_queue_count; int flags; TYPE_1__ io_watcher; } ;
typedef  TYPE_2__ uv_udp_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct msghdr {unsigned int msg_namelen; unsigned int msg_iovlen; struct iovec* msg_iov; struct sockaddr* msg_name; } ;
struct iovec {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ ENOBUFS ; 
 scalar_t__ EWOULDBLOCK ; 
 int UV_EAGAIN ; 
 int UV_HANDLE_UDP_CONNECTED ; 
 int UV__ERR (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 int sendmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 
 int uv__udp_maybe_deferred_bind (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int uv__udp_try_send(uv_udp_t* handle,
                     const uv_buf_t bufs[],
                     unsigned int nbufs,
                     const struct sockaddr* addr,
                     unsigned int addrlen) {
  int err;
  struct msghdr h;
  ssize_t size;

  assert(nbufs > 0);

  /* already sending a message */
  if (handle->send_queue_count != 0)
    return UV_EAGAIN;

  if (addr) {
    err = uv__udp_maybe_deferred_bind(handle, addr->sa_family, 0);
    if (err)
      return err;
  } else {
    assert(handle->flags & UV_HANDLE_UDP_CONNECTED);
  }

  memset(&h, 0, sizeof h);
  h.msg_name = (struct sockaddr*) addr;
  h.msg_namelen = addrlen;
  h.msg_iov = (struct iovec*) bufs;
  h.msg_iovlen = nbufs;

  do {
    size = sendmsg(handle->io_watcher.fd, &h, 0);
  } while (size == -1 && errno == EINTR);

  if (size == -1) {
    if (errno == EAGAIN || errno == EWOULDBLOCK || errno == ENOBUFS)
      return UV_EAGAIN;
    else
      return UV__ERR(errno);
  }

  return size;
}