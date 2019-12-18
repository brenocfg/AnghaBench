#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ socket; int delayed_error; int /*<<< orphan*/  flags; int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_tcp_t ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  scalar_t__ SOCKET ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int ERROR_INVALID_PARAMETER ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  UV_HANDLE_BOUND ; 
 unsigned int UV_TCP_IPV6ONLY ; 
 int WSAEADDRINUSE ; 
 int WSAGetLastError () ; 
 int bind (scalar_t__,struct sockaddr const*,unsigned int) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_tcp_set_socket (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uv_tcp_try_bind(uv_tcp_t* handle,
                           const struct sockaddr* addr,
                           unsigned int addrlen,
                           unsigned int flags) {
  DWORD err;
  int r;

  if (handle->socket == INVALID_SOCKET) {
    SOCKET sock;

    /* Cannot set IPv6-only mode on non-IPv6 socket. */
    if ((flags & UV_TCP_IPV6ONLY) && addr->sa_family != AF_INET6)
      return ERROR_INVALID_PARAMETER;

    sock = socket(addr->sa_family, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
      return WSAGetLastError();
    }

    err = uv_tcp_set_socket(handle->loop, handle, sock, addr->sa_family, 0);
    if (err) {
      closesocket(sock);
      return err;
    }
  }

#ifdef IPV6_V6ONLY
  if (addr->sa_family == AF_INET6) {
    int on;

    on = (flags & UV_TCP_IPV6ONLY) != 0;

    /* TODO: how to handle errors? This may fail if there is no ipv4 stack
     * available, or when run on XP/2003 which have no support for dualstack
     * sockets. For now we're silently ignoring the error. */
    setsockopt(handle->socket,
               IPPROTO_IPV6,
               IPV6_V6ONLY,
               (const char*)&on,
               sizeof on);
  }
#endif

  r = bind(handle->socket, addr, addrlen);

  if (r == SOCKET_ERROR) {
    err = WSAGetLastError();
    if (err == WSAEADDRINUSE) {
      /* Some errors are not to be reported until connect() or listen() */
      handle->delayed_error = err;
    } else {
      return err;
    }
  }

  handle->flags |= UV_HANDLE_BOUND;

  return 0;
}