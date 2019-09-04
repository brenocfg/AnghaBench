#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uv_tcp_t ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int WSAGetLastError () ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int uv__tcp_nodelay(uv_tcp_t* handle, SOCKET socket, int enable) {
  if (setsockopt(socket,
                 IPPROTO_TCP,
                 TCP_NODELAY,
                 (const char*)&enable,
                 sizeof enable) == -1) {
    return WSAGetLastError();
  }
  return 0;
}