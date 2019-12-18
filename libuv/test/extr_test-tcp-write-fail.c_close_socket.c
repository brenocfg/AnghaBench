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
typedef  int /*<<< orphan*/  uv_os_sock_t ;
typedef  scalar_t__ uv_os_fd_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int close (scalar_t__) ; 
 int closesocket (int /*<<< orphan*/ ) ; 
 int uv_fileno (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static void close_socket(uv_tcp_t* sock) {
  uv_os_fd_t fd;
  int r;

  r = uv_fileno((uv_handle_t*)sock, &fd);
  ASSERT(r == 0);
#ifdef _WIN32
  r = closesocket((uv_os_sock_t)fd);
#else
  r = close(fd);
#endif
  ASSERT(r == 0);
}