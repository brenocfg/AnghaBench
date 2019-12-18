#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
struct TYPE_37__ {scalar_t__ len; int /*<<< orphan*/ * base; } ;
struct TYPE_35__ {scalar_t__ type; int flags; int /*<<< orphan*/  (* recv_cb ) (TYPE_4__*,scalar_t__,TYPE_6__*,struct sockaddr const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  socket; int /*<<< orphan*/  (* alloc_cb ) (int /*<<< orphan*/ *,int,TYPE_6__*) ;int /*<<< orphan*/  recv_from; TYPE_6__ recv_buffer; } ;
typedef  TYPE_4__ uv_udp_t ;
struct TYPE_32__ {scalar_t__ InternalHigh; } ;
struct TYPE_33__ {TYPE_1__ overlapped; } ;
struct TYPE_34__ {TYPE_2__ io; } ;
struct TYPE_36__ {TYPE_3__ u; } ;
typedef  TYPE_5__ uv_req_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  TYPE_6__ uv_buf_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  WSABUF ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DECREASE_PENDING_REQ_COUNT (TYPE_4__*) ; 
 scalar_t__ GET_REQ_SOCK_ERROR (TYPE_5__*) ; 
 int /*<<< orphan*/  REQ_SUCCESS (TYPE_5__*) ; 
 scalar_t__ SOCKET_ERROR ; 
 scalar_t__ UV_ENOBUFS ; 
 int UV_HANDLE_READING ; 
 int UV_HANDLE_READ_PENDING ; 
 int UV_HANDLE_ZERO_READ ; 
 scalar_t__ UV_UDP ; 
 int /*<<< orphan*/  UV_UDP_PARTIAL ; 
 scalar_t__ WSAECONNRESET ; 
 scalar_t__ WSAEMSGSIZE ; 
 scalar_t__ WSAENETRESET ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ WSARecvFrom (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__*,scalar_t__*,struct sockaddr*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,scalar_t__,TYPE_6__*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,scalar_t__,TYPE_6__*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int,TYPE_6__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,scalar_t__,TYPE_6__*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_4__*,scalar_t__,TYPE_6__*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_4__*,scalar_t__,TYPE_6__*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (TYPE_4__*,scalar_t__,TYPE_6__*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (TYPE_4__*,scalar_t__,TYPE_6__*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (TYPE_4__*,scalar_t__,TYPE_6__*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 TYPE_6__ uv_buf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_translate_sys_error (scalar_t__) ; 
 int /*<<< orphan*/  uv_udp_queue_recv (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  uv_udp_recv_stop (TYPE_4__*) ; 

void uv_process_udp_recv_req(uv_loop_t* loop, uv_udp_t* handle,
    uv_req_t* req) {
  uv_buf_t buf;
  int partial;

  assert(handle->type == UV_UDP);

  handle->flags &= ~UV_HANDLE_READ_PENDING;

  if (!REQ_SUCCESS(req)) {
    DWORD err = GET_REQ_SOCK_ERROR(req);
    if (err == WSAEMSGSIZE) {
      /* Not a real error, it just indicates that the received packet was
       * bigger than the receive buffer. */
    } else if (err == WSAECONNRESET || err == WSAENETRESET) {
      /* A previous sendto operation failed; ignore this error. If zero-reading
       * we need to call WSARecv/WSARecvFrom _without_ the. MSG_PEEK flag to
       * clear out the error queue. For nonzero reads, immediately queue a new
       * receive. */
      if (!(handle->flags & UV_HANDLE_ZERO_READ)) {
        goto done;
      }
    } else {
      /* A real error occurred. Report the error to the user only if we're
       * currently reading. */
      if (handle->flags & UV_HANDLE_READING) {
        uv_udp_recv_stop(handle);
        buf = (handle->flags & UV_HANDLE_ZERO_READ) ?
              uv_buf_init(NULL, 0) : handle->recv_buffer;
        handle->recv_cb(handle, uv_translate_sys_error(err), &buf, NULL, 0);
      }
      goto done;
    }
  }

  if (!(handle->flags & UV_HANDLE_ZERO_READ)) {
    /* Successful read */
    partial = !REQ_SUCCESS(req);
    handle->recv_cb(handle,
                    req->u.io.overlapped.InternalHigh,
                    &handle->recv_buffer,
                    (const struct sockaddr*) &handle->recv_from,
                    partial ? UV_UDP_PARTIAL : 0);
  } else if (handle->flags & UV_HANDLE_READING) {
    DWORD bytes, err, flags;
    struct sockaddr_storage from;
    int from_len;

    /* Do a nonblocking receive.
     * TODO: try to read multiple datagrams at once. FIONREAD maybe? */
    buf = uv_buf_init(NULL, 0);
    handle->alloc_cb((uv_handle_t*) handle, 65536, &buf);
    if (buf.base == NULL || buf.len == 0) {
      handle->recv_cb(handle, UV_ENOBUFS, &buf, NULL, 0);
      goto done;
    }
    assert(buf.base != NULL);

    memset(&from, 0, sizeof from);
    from_len = sizeof from;

    flags = 0;

    if (WSARecvFrom(handle->socket,
                    (WSABUF*)&buf,
                    1,
                    &bytes,
                    &flags,
                    (struct sockaddr*) &from,
                    &from_len,
                    NULL,
                    NULL) != SOCKET_ERROR) {

      /* Message received */
      handle->recv_cb(handle, bytes, &buf, (const struct sockaddr*) &from, 0);
    } else {
      err = WSAGetLastError();
      if (err == WSAEMSGSIZE) {
        /* Message truncated */
        handle->recv_cb(handle,
                        bytes,
                        &buf,
                        (const struct sockaddr*) &from,
                        UV_UDP_PARTIAL);
      } else if (err == WSAEWOULDBLOCK) {
        /* Kernel buffer empty */
        handle->recv_cb(handle, 0, &buf, NULL, 0);
      } else if (err == WSAECONNRESET || err == WSAENETRESET) {
        /* WSAECONNRESET/WSANETRESET is ignored because this just indicates
         * that a previous sendto operation failed.
         */
        handle->recv_cb(handle, 0, &buf, NULL, 0);
      } else {
        /* Any other error that we want to report back to the user. */
        uv_udp_recv_stop(handle);
        handle->recv_cb(handle, uv_translate_sys_error(err), &buf, NULL, 0);
      }
    }
  }

done:
  /* Post another read if still reading and not closing. */
  if ((handle->flags & UV_HANDLE_READING) &&
      !(handle->flags & UV_HANDLE_READ_PENDING)) {
    uv_udp_queue_recv(loop, handle);
  }

  DECREASE_PENDING_REQ_COUNT(handle);
}