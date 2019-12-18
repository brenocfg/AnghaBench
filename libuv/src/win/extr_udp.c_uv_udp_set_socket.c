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
struct TYPE_8__ {scalar_t__ socket; int flags; int /*<<< orphan*/  func_wsarecvfrom; int /*<<< orphan*/  func_wsarecv; } ;
typedef  TYPE_2__ uv_udp_t ;
struct TYPE_9__ {int /*<<< orphan*/  iocp; } ;
typedef  TYPE_3__ uv_loop_t ;
struct TYPE_7__ {int ChainLen; } ;
struct TYPE_10__ {TYPE_1__ ProtocolChain; } ;
typedef  TYPE_4__ WSAPROTOCOL_INFOW ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  scalar_t__ SOCKET ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int AF_INET6 ; 
 int /*<<< orphan*/ * CreateIoCompletionPort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INVALID_FUNCTION ; 
 int FILE_SKIP_COMPLETION_PORT_ON_SUCCESS ; 
 int FILE_SKIP_SET_EVENT_ON_HANDLE ; 
 int /*<<< orphan*/  FIONBIO ; 
 int GetLastError () ; 
 int /*<<< orphan*/  HANDLE_FLAG_INHERIT ; 
 scalar_t__ INVALID_SOCKET ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_PROTOCOL_INFOW ; 
 scalar_t__ SetFileCompletionNotificationModes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetHandleInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UV_EBUSY ; 
 int UV_HANDLE_IPV6 ; 
 int UV_HANDLE_SYNC_BYPASS_IOCP ; 
 int WSAGetLastError () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ getsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ ioctlsocket (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  uv_wsarecv_workaround ; 
 int /*<<< orphan*/  uv_wsarecvfrom_workaround ; 

__attribute__((used)) static int uv_udp_set_socket(uv_loop_t* loop, uv_udp_t* handle, SOCKET socket,
    int family) {
  DWORD yes = 1;
  WSAPROTOCOL_INFOW info;
  int opt_len;

  if (handle->socket != INVALID_SOCKET)
    return UV_EBUSY;

  /* Set the socket to nonblocking mode */
  if (ioctlsocket(socket, FIONBIO, &yes) == SOCKET_ERROR) {
    return WSAGetLastError();
  }

  /* Make the socket non-inheritable */
  if (!SetHandleInformation((HANDLE)socket, HANDLE_FLAG_INHERIT, 0)) {
    return GetLastError();
  }

  /* Associate it with the I/O completion port. Use uv_handle_t pointer as
   * completion key. */
  if (CreateIoCompletionPort((HANDLE)socket,
                             loop->iocp,
                             (ULONG_PTR)socket,
                             0) == NULL) {
    return GetLastError();
  }

  /* All known Windows that support SetFileCompletionNotificationModes have a
   * bug that makes it impossible to use this function in conjunction with
   * datagram sockets. We can work around that but only if the user is using
   * the default UDP driver (AFD) and has no other. LSPs stacked on top. Here
   * we check whether that is the case. */
  opt_len = (int) sizeof info;
  if (getsockopt(
          socket, SOL_SOCKET, SO_PROTOCOL_INFOW, (char*) &info, &opt_len) ==
      SOCKET_ERROR) {
    return GetLastError();
  }

  if (info.ProtocolChain.ChainLen == 1) {
    if (SetFileCompletionNotificationModes(
            (HANDLE) socket,
            FILE_SKIP_SET_EVENT_ON_HANDLE |
                FILE_SKIP_COMPLETION_PORT_ON_SUCCESS)) {
      handle->flags |= UV_HANDLE_SYNC_BYPASS_IOCP;
      handle->func_wsarecv = uv_wsarecv_workaround;
      handle->func_wsarecvfrom = uv_wsarecvfrom_workaround;
    } else if (GetLastError() != ERROR_INVALID_FUNCTION) {
      return GetLastError();
    }
  }

  handle->socket = socket;

  if (family == AF_INET6) {
    handle->flags |= UV_HANDLE_IPV6;
  } else {
    assert(!(handle->flags & UV_HANDLE_IPV6));
  }

  return 0;
}