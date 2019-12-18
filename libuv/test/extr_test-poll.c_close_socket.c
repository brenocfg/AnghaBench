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
 scalar_t__ ECONNRESET ; 
 int close (int /*<<< orphan*/ ) ; 
 int closesocket (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 

__attribute__((used)) static void close_socket(uv_os_sock_t sock) {
  int r;
#ifdef _WIN32
  r = closesocket(sock);
#else
  r = close(sock);
#endif
  /* On FreeBSD close() can fail with ECONNRESET if the socket was shutdown by
   * the peer before all pending data was delivered.
   */
  ASSERT(r == 0 || errno == ECONNRESET);
}