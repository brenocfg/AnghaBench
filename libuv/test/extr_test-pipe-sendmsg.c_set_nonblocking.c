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
typedef  int /*<<< orphan*/  uv_os_sock_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ioctlsocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void set_nonblocking(uv_os_sock_t sock) {
  int r;
#ifdef _WIN32
  unsigned long on = 1;
  r = ioctlsocket(sock, FIONBIO, &on);
  ASSERT(r == 0);
#else
  int flags = fcntl(sock, F_GETFL, 0);
  ASSERT(flags >= 0);
  r = fcntl(sock, F_SETFL, flags | O_NONBLOCK);
  ASSERT(r >= 0);
#endif
}