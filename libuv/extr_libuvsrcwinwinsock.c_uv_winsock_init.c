#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int dwServiceFlags1; } ;
typedef  TYPE_1__ WSAPROTOCOL_INFOW ;
typedef  int /*<<< orphan*/  WSADATA ;
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  SM_CLEANBOOT ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_PROTOCOL_INFOW ; 
 int WSAGetLastError () ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int XP1_IFS_HANDLES ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ closesocket (scalar_t__) ; 
 int /*<<< orphan*/  error_means_no_support (int) ; 
 scalar_t__ getsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_addr_ip4_any_ ; 
 int /*<<< orphan*/  uv_addr_ip6_any_ ; 
 int /*<<< orphan*/  uv_fatal_error (int,char*) ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_ip6_addr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_tcp_non_ifs_lsp_ipv4 ; 
 int uv_tcp_non_ifs_lsp_ipv6 ; 

void uv_winsock_init(void) {
  WSADATA wsa_data;
  int errorno;
  SOCKET dummy;
  WSAPROTOCOL_INFOW protocol_info;
  int opt_len;

  /* Set implicit binding address used by connectEx */
  if (uv_ip4_addr("0.0.0.0", 0, &uv_addr_ip4_any_)) {
    abort();
  }

  if (uv_ip6_addr("::", 0, &uv_addr_ip6_any_)) {
    abort();
  }

  /* Skip initialization in safe mode without network support */
  if (1 == GetSystemMetrics(SM_CLEANBOOT)) return;

  /* Initialize winsock */
  errorno = WSAStartup(MAKEWORD(2, 2), &wsa_data);
  if (errorno != 0) {
    uv_fatal_error(errorno, "WSAStartup");
  }

  /* Detect non-IFS LSPs */
  dummy = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

  if (dummy != INVALID_SOCKET) {
    opt_len = (int) sizeof protocol_info;
    if (getsockopt(dummy,
                   SOL_SOCKET,
                   SO_PROTOCOL_INFOW,
                   (char*) &protocol_info,
                   &opt_len) == SOCKET_ERROR)
      uv_fatal_error(WSAGetLastError(), "getsockopt");

    if (!(protocol_info.dwServiceFlags1 & XP1_IFS_HANDLES))
      uv_tcp_non_ifs_lsp_ipv4 = 1;

    if (closesocket(dummy) == SOCKET_ERROR)
      uv_fatal_error(WSAGetLastError(), "closesocket");

  } else if (!error_means_no_support(WSAGetLastError())) {
    /* Any error other than "socket type not supported" is fatal. */
    uv_fatal_error(WSAGetLastError(), "socket");
  }

  /* Detect IPV6 support and non-IFS LSPs */
  dummy = socket(AF_INET6, SOCK_STREAM, IPPROTO_IP);

  if (dummy != INVALID_SOCKET) {
    opt_len = (int) sizeof protocol_info;
    if (getsockopt(dummy,
                   SOL_SOCKET,
                   SO_PROTOCOL_INFOW,
                   (char*) &protocol_info,
                   &opt_len) == SOCKET_ERROR)
      uv_fatal_error(WSAGetLastError(), "getsockopt");

    if (!(protocol_info.dwServiceFlags1 & XP1_IFS_HANDLES))
      uv_tcp_non_ifs_lsp_ipv6 = 1;

    if (closesocket(dummy) == SOCKET_ERROR)
      uv_fatal_error(WSAGetLastError(), "closesocket");

  } else if (!error_means_no_support(WSAGetLastError())) {
    /* Any error other than "socket type not supported" is fatal. */
    uv_fatal_error(WSAGetLastError(), "socket");
  }
}