#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ processed_accepts; int /*<<< orphan*/ * func_acceptex; int /*<<< orphan*/ * pending_accepts; int /*<<< orphan*/ * accept_reqs; } ;
struct TYPE_7__ {int /*<<< orphan*/ * func_connectex; } ;
struct TYPE_9__ {TYPE_2__ serv; TYPE_1__ conn; } ;
struct TYPE_10__ {int /*<<< orphan*/  handle_queue; int /*<<< orphan*/  loop; scalar_t__ delayed_error; TYPE_3__ tcp; scalar_t__ reqs_pending; scalar_t__ socket; } ;
typedef  TYPE_4__ uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  scalar_t__ SOCKET ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int AF_UNSPEC ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  QUEUE_REMOVE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int UV_EINVAL ; 
 int /*<<< orphan*/  UV_TCP ; 
 scalar_t__ WSAGetLastError () ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 scalar_t__ socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_stream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_tcp_set_socket (int /*<<< orphan*/ ,TYPE_4__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int uv_translate_sys_error (scalar_t__) ; 

int uv_tcp_init_ex(uv_loop_t* loop, uv_tcp_t* handle, unsigned int flags) {
  int domain;

  /* Use the lower 8 bits for the domain */
  domain = flags & 0xFF;
  if (domain != AF_INET && domain != AF_INET6 && domain != AF_UNSPEC)
    return UV_EINVAL;

  if (flags & ~0xFF)
    return UV_EINVAL;

  uv_stream_init(loop, (uv_stream_t*) handle, UV_TCP);
  handle->tcp.serv.accept_reqs = NULL;
  handle->tcp.serv.pending_accepts = NULL;
  handle->socket = INVALID_SOCKET;
  handle->reqs_pending = 0;
  handle->tcp.serv.func_acceptex = NULL;
  handle->tcp.conn.func_connectex = NULL;
  handle->tcp.serv.processed_accepts = 0;
  handle->delayed_error = 0;

  /* If anything fails beyond this point we need to remove the handle from
   * the handle queue, since it was added by uv__handle_init in uv_stream_init.
   */

  if (domain != AF_UNSPEC) {
    SOCKET sock;
    DWORD err;

    sock = socket(domain, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
      err = WSAGetLastError();
      QUEUE_REMOVE(&handle->handle_queue);
      return uv_translate_sys_error(err);
    }

    err = uv_tcp_set_socket(handle->loop, handle, sock, domain, 0);
    if (err) {
      closesocket(sock);
      QUEUE_REMOVE(&handle->handle_queue);
      return uv_translate_sys_error(err);
    }

  }

  return 0;
}