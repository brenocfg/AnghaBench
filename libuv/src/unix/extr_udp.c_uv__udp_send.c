#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ send_queue_count; int flags; int /*<<< orphan*/  io_watcher; int /*<<< orphan*/  loop; int /*<<< orphan*/  write_queue; int /*<<< orphan*/  send_queue_size; } ;
typedef  TYPE_1__ uv_udp_t ;
struct TYPE_16__ {int /*<<< orphan*/  ss_family; } ;
struct TYPE_15__ {unsigned int nbufs; int /*<<< orphan*/  queue; TYPE_9__* bufs; TYPE_9__* bufsml; TYPE_1__* handle; int /*<<< orphan*/  send_cb; TYPE_9__ addr; } ;
typedef  TYPE_2__ uv_udp_send_t ;
typedef  int /*<<< orphan*/  uv_udp_send_cb ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
typedef  struct sockaddr uv_buf_t ;
typedef  int /*<<< orphan*/  bufs ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 unsigned int ARRAY_SIZE (TYPE_9__*) ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  QUEUE_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QUEUE_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int UV_ENOMEM ; 
 int UV_HANDLE_UDP_PROCESSING ; 
 int /*<<< orphan*/  UV_UDP_SEND ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_9__*,struct sockaddr const*,unsigned int) ; 
 scalar_t__ uv__count_bufs (TYPE_9__*,unsigned int) ; 
 int /*<<< orphan*/  uv__handle_start (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__io_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_9__* uv__malloc (unsigned int) ; 
 int /*<<< orphan*/  uv__req_init (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__req_unregister (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int uv__udp_maybe_deferred_bind (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__udp_sendmsg (TYPE_1__*) ; 

int uv__udp_send(uv_udp_send_t* req,
                 uv_udp_t* handle,
                 const uv_buf_t bufs[],
                 unsigned int nbufs,
                 const struct sockaddr* addr,
                 unsigned int addrlen,
                 uv_udp_send_cb send_cb) {
  int err;
  int empty_queue;

  assert(nbufs > 0);

  if (addr) {
    err = uv__udp_maybe_deferred_bind(handle, addr->sa_family, 0);
    if (err)
      return err;
  }

  /* It's legal for send_queue_count > 0 even when the write_queue is empty;
   * it means there are error-state requests in the write_completed_queue that
   * will touch up send_queue_size/count later.
   */
  empty_queue = (handle->send_queue_count == 0);

  uv__req_init(handle->loop, req, UV_UDP_SEND);
  assert(addrlen <= sizeof(req->addr));
  if (addr == NULL)
    req->addr.ss_family = AF_UNSPEC;
  else
    memcpy(&req->addr, addr, addrlen);
  req->send_cb = send_cb;
  req->handle = handle;
  req->nbufs = nbufs;

  req->bufs = req->bufsml;
  if (nbufs > ARRAY_SIZE(req->bufsml))
    req->bufs = uv__malloc(nbufs * sizeof(bufs[0]));

  if (req->bufs == NULL) {
    uv__req_unregister(handle->loop, req);
    return UV_ENOMEM;
  }

  memcpy(req->bufs, bufs, nbufs * sizeof(bufs[0]));
  handle->send_queue_size += uv__count_bufs(req->bufs, req->nbufs);
  handle->send_queue_count++;
  QUEUE_INSERT_TAIL(&handle->write_queue, &req->queue);
  uv__handle_start(handle);

  if (empty_queue && !(handle->flags & UV_HANDLE_UDP_PROCESSING)) {
    uv__udp_sendmsg(handle);

    /* `uv__udp_sendmsg` may not be able to do non-blocking write straight
     * away. In such cases the `io_watcher` has to be queued for asynchronous
     * write.
     */
    if (!QUEUE_EMPTY(&handle->write_queue))
      uv__io_start(handle->loop, &handle->io_watcher, POLLOUT);
  } else {
    uv__io_start(handle->loop, &handle->io_watcher, POLLOUT);
  }

  return 0;
}