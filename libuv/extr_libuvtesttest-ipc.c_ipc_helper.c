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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BACKLOG ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  channel ; 
 int close_cb_called ; 
 int connection_accepted ; 
 int /*<<< orphan*/  ipc_on_connection ; 
 int /*<<< orphan*/  notify_parent_process () ; 
 int /*<<< orphan*/  tcp_server ; 
 int /*<<< orphan*/  uv_buf_init (char*,int) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 scalar_t__ uv_is_closing (int /*<<< orphan*/ *) ; 
 int uv_is_readable (int /*<<< orphan*/ *) ; 
 int uv_is_writable (int /*<<< orphan*/ *) ; 
 int uv_listen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_pipe_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uv_pipe_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_tcp_bind (int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_write2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_req ; 

int ipc_helper(int listen_after_write) {
  /*
   * This is launched from test-ipc.c. stdin is a duplex channel that we
   * over which a handle will be transmitted.
   */
  struct sockaddr_in addr;
  int r;
  uv_buf_t buf;

  ASSERT(0 == uv_ip4_addr("0.0.0.0", TEST_PORT, &addr));

  r = uv_pipe_init(uv_default_loop(), &channel, 1);
  ASSERT(r == 0);

  uv_pipe_open(&channel, 0);

  ASSERT(1 == uv_is_readable((uv_stream_t*) &channel));
  ASSERT(1 == uv_is_writable((uv_stream_t*) &channel));
  ASSERT(0 == uv_is_closing((uv_handle_t*) &channel));

  r = uv_tcp_init(uv_default_loop(), &tcp_server);
  ASSERT(r == 0);

  r = uv_tcp_bind(&tcp_server, (const struct sockaddr*) &addr, 0);
  ASSERT(r == 0);

  if (!listen_after_write) {
    r = uv_listen((uv_stream_t*)&tcp_server, BACKLOG, ipc_on_connection);
    ASSERT(r == 0);
  }

  buf = uv_buf_init("hello\n", 6);
  r = uv_write2(&write_req, (uv_stream_t*)&channel, &buf, 1,
      (uv_stream_t*)&tcp_server, NULL);
  ASSERT(r == 0);

  if (listen_after_write) {
    r = uv_listen((uv_stream_t*)&tcp_server, BACKLOG, ipc_on_connection);
    ASSERT(r == 0);
  }

  notify_parent_process();
  r = uv_run(uv_default_loop(), UV_RUN_DEFAULT);
  ASSERT(r == 0);

  ASSERT(connection_accepted == 1);
  ASSERT(close_cb_called == 3);

  MAKE_VALGRIND_HAPPY();
  return 0;
}