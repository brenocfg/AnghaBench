#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  handle_queue; int /*<<< orphan*/  loop; TYPE_4__ recv_req; scalar_t__ send_queue_count; scalar_t__ send_queue_size; int /*<<< orphan*/  func_wsarecvfrom; int /*<<< orphan*/  func_wsarecv; scalar_t__ activecnt; scalar_t__ reqs_pending; scalar_t__ socket; } ;
typedef  TYPE_1__ uv_udp_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  scalar_t__ SOCKET ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int AF_UNSPEC ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  QUEUE_REMOVE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int UV_EINVAL ; 
 int /*<<< orphan*/  UV_REQ_INIT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UV_UDP ; 
 int /*<<< orphan*/  UV_UDP_RECV ; 
 scalar_t__ WSAGetLastError () ; 
 int /*<<< orphan*/  WSARecv ; 
 int /*<<< orphan*/  WSARecvFrom ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 scalar_t__ socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__handle_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_translate_sys_error (scalar_t__) ; 
 scalar_t__ uv_udp_set_socket (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,int) ; 

int uv_udp_init_ex(uv_loop_t* loop, uv_udp_t* handle, unsigned int flags) {
  int domain;

  /* Use the lower 8 bits for the domain */
  domain = flags & 0xFF;
  if (domain != AF_INET && domain != AF_INET6 && domain != AF_UNSPEC)
    return UV_EINVAL;

  if (flags & ~0xFF)
    return UV_EINVAL;

  uv__handle_init(loop, (uv_handle_t*) handle, UV_UDP);
  handle->socket = INVALID_SOCKET;
  handle->reqs_pending = 0;
  handle->activecnt = 0;
  handle->func_wsarecv = WSARecv;
  handle->func_wsarecvfrom = WSARecvFrom;
  handle->send_queue_size = 0;
  handle->send_queue_count = 0;
  UV_REQ_INIT(&handle->recv_req, UV_UDP_RECV);
  handle->recv_req.data = handle;

  /* If anything fails beyond this point we need to remove the handle from
   * the handle queue, since it was added by uv__handle_init.
   */

  if (domain != AF_UNSPEC) {
    SOCKET sock;
    DWORD err;

    sock = socket(domain, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
      err = WSAGetLastError();
      QUEUE_REMOVE(&handle->handle_queue);
      return uv_translate_sys_error(err);
    }

    err = uv_udp_set_socket(handle->loop, handle, sock, domain);
    if (err) {
      closesocket(sock);
      QUEUE_REMOVE(&handle->handle_queue);
      return uv_translate_sys_error(err);
    }
  }

  return 0;
}