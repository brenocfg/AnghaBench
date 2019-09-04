#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ wait_handle; int /*<<< orphan*/ * event_handle; } ;
struct TYPE_21__ {TYPE_7__* accept_reqs; } ;
struct TYPE_22__ {TYPE_3__ serv; } ;
struct TYPE_19__ {scalar_t__ write_reqs_pending; TYPE_13__* shutdown_req; } ;
struct TYPE_20__ {TYPE_1__ conn; } ;
struct TYPE_24__ {int flags; scalar_t__ reqs_pending; TYPE_5__ read_req; TYPE_4__ tcp; int /*<<< orphan*/  socket; TYPE_2__ stream; } ;
typedef  TYPE_6__ uv_tcp_t ;
struct TYPE_25__ {scalar_t__ wait_handle; int /*<<< orphan*/ * event_handle; } ;
typedef  TYPE_7__ uv_tcp_accept_t ;
struct TYPE_26__ {int /*<<< orphan*/  active_tcp_streams; } ;
typedef  TYPE_8__ uv_loop_t ;
struct TYPE_18__ {int /*<<< orphan*/  (* cb ) (TYPE_13__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DECREASE_PENDING_REQ_COUNT (TYPE_6__*) ; 
 int ERROR_OPERATION_ABORTED ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int /*<<< orphan*/  SD_SEND ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  UNREGISTER_HANDLE_REQ (TYPE_8__*,TYPE_6__*,TYPE_13__*) ; 
 int UV_HANDLE_CLOSED ; 
 int UV_HANDLE_CLOSING ; 
 int UV_HANDLE_CONNECTION ; 
 int UV_HANDLE_EMULATE_IOCP ; 
 int UV_HANDLE_TCP_SOCKET_CLOSED ; 
 int /*<<< orphan*/  UnregisterWait (scalar_t__) ; 
 int WSAGetLastError () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 scalar_t__ shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__free (TYPE_7__*) ; 
 int /*<<< orphan*/  uv__handle_close (TYPE_6__*) ; 
 unsigned int uv_simultaneous_server_accepts ; 
 int /*<<< orphan*/  uv_translate_sys_error (int) ; 

void uv_tcp_endgame(uv_loop_t* loop, uv_tcp_t* handle) {
  int err;
  unsigned int i;
  uv_tcp_accept_t* req;

  if (handle->flags & UV_HANDLE_CONNECTION &&
      handle->stream.conn.shutdown_req != NULL &&
      handle->stream.conn.write_reqs_pending == 0) {

    UNREGISTER_HANDLE_REQ(loop, handle, handle->stream.conn.shutdown_req);

    err = 0;
    if (handle->flags & UV_HANDLE_CLOSING) {
      err = ERROR_OPERATION_ABORTED;
    } else if (shutdown(handle->socket, SD_SEND) == SOCKET_ERROR) {
      err = WSAGetLastError();
    }

    if (handle->stream.conn.shutdown_req->cb) {
      handle->stream.conn.shutdown_req->cb(handle->stream.conn.shutdown_req,
                               uv_translate_sys_error(err));
    }

    handle->stream.conn.shutdown_req = NULL;
    DECREASE_PENDING_REQ_COUNT(handle);
    return;
  }

  if (handle->flags & UV_HANDLE_CLOSING &&
      handle->reqs_pending == 0) {
    assert(!(handle->flags & UV_HANDLE_CLOSED));

    if (!(handle->flags & UV_HANDLE_TCP_SOCKET_CLOSED)) {
      closesocket(handle->socket);
      handle->socket = INVALID_SOCKET;
      handle->flags |= UV_HANDLE_TCP_SOCKET_CLOSED;
    }

    if (!(handle->flags & UV_HANDLE_CONNECTION) && handle->tcp.serv.accept_reqs) {
      if (handle->flags & UV_HANDLE_EMULATE_IOCP) {
        for (i = 0; i < uv_simultaneous_server_accepts; i++) {
          req = &handle->tcp.serv.accept_reqs[i];
          if (req->wait_handle != INVALID_HANDLE_VALUE) {
            UnregisterWait(req->wait_handle);
            req->wait_handle = INVALID_HANDLE_VALUE;
          }
          if (req->event_handle) {
            CloseHandle(req->event_handle);
            req->event_handle = NULL;
          }
        }
      }

      uv__free(handle->tcp.serv.accept_reqs);
      handle->tcp.serv.accept_reqs = NULL;
    }

    if (handle->flags & UV_HANDLE_CONNECTION &&
        handle->flags & UV_HANDLE_EMULATE_IOCP) {
      if (handle->read_req.wait_handle != INVALID_HANDLE_VALUE) {
        UnregisterWait(handle->read_req.wait_handle);
        handle->read_req.wait_handle = INVALID_HANDLE_VALUE;
      }
      if (handle->read_req.event_handle) {
        CloseHandle(handle->read_req.event_handle);
        handle->read_req.event_handle = NULL;
      }
    }

    uv__handle_close(handle);
    loop->active_tcp_streams--;
  }
}