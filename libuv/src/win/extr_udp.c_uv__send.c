#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  send_queue_count; int /*<<< orphan*/  send_queue_size; int /*<<< orphan*/  reqs_pending; int /*<<< orphan*/  socket; int /*<<< orphan*/ * loop; } ;
typedef  TYPE_3__ uv_udp_t ;
struct TYPE_10__ {scalar_t__ queued_bytes; int /*<<< orphan*/  overlapped; } ;
struct TYPE_11__ {TYPE_1__ io; } ;
struct TYPE_13__ {TYPE_2__ u; int /*<<< orphan*/  cb; TYPE_3__* handle; } ;
typedef  TYPE_4__ uv_udp_send_t ;
typedef  int /*<<< orphan*/  uv_udp_send_cb ;
typedef  int /*<<< orphan*/  uv_req_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  WSABUF ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  REGISTER_HANDLE_REQ (int /*<<< orphan*/ *,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  UV_REQ_INIT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ UV_SUCCEEDED_WITHOUT_IOCP (int) ; 
 scalar_t__ UV_SUCCEEDED_WITH_IOCP (int) ; 
 int /*<<< orphan*/  UV_UDP_SEND ; 
 int WSAGetLastError () ; 
 scalar_t__ WSASendTo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,scalar_t__*,int /*<<< orphan*/ ,struct sockaddr const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uv__count_bufs (int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  uv_insert_pending_req (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uv__send(uv_udp_send_t* req,
                    uv_udp_t* handle,
                    const uv_buf_t bufs[],
                    unsigned int nbufs,
                    const struct sockaddr* addr,
                    unsigned int addrlen,
                    uv_udp_send_cb cb) {
  uv_loop_t* loop = handle->loop;
  DWORD result, bytes;

  UV_REQ_INIT(req, UV_UDP_SEND);
  req->handle = handle;
  req->cb = cb;
  memset(&req->u.io.overlapped, 0, sizeof(req->u.io.overlapped));

  result = WSASendTo(handle->socket,
                     (WSABUF*)bufs,
                     nbufs,
                     &bytes,
                     0,
                     addr,
                     addrlen,
                     &req->u.io.overlapped,
                     NULL);

  if (UV_SUCCEEDED_WITHOUT_IOCP(result == 0)) {
    /* Request completed immediately. */
    req->u.io.queued_bytes = 0;
    handle->reqs_pending++;
    handle->send_queue_size += req->u.io.queued_bytes;
    handle->send_queue_count++;
    REGISTER_HANDLE_REQ(loop, handle, req);
    uv_insert_pending_req(loop, (uv_req_t*)req);
  } else if (UV_SUCCEEDED_WITH_IOCP(result == 0)) {
    /* Request queued by the kernel. */
    req->u.io.queued_bytes = uv__count_bufs(bufs, nbufs);
    handle->reqs_pending++;
    handle->send_queue_size += req->u.io.queued_bytes;
    handle->send_queue_count++;
    REGISTER_HANDLE_REQ(loop, handle, req);
  } else {
    /* Send failed due to an error. */
    return WSAGetLastError();
  }

  return 0;
}