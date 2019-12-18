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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int uv_os_sock_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int _get_osfhandle (int) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_listen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_tcp_open (int /*<<< orphan*/ *,int) ; 

int spawn_tcp_server_helper(void) {
  uv_tcp_t tcp;
  uv_os_sock_t handle;
  int r;

  r = uv_tcp_init(uv_default_loop(), &tcp);
  ASSERT(r == 0);

#ifdef _WIN32
  handle = _get_osfhandle(3);
#else
  handle = 3;
#endif
  r = uv_tcp_open(&tcp, handle);
  ASSERT(r == 0);

  /* Make sure that we can listen on a socket that was
   * passed down from the parent process
   */
  r = uv_listen((uv_stream_t*)&tcp, SOMAXCONN, NULL);
  ASSERT(r == 0);

  return 1;
}