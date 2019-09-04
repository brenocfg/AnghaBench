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
typedef  int /*<<< orphan*/  uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; int /*<<< orphan*/  conn_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BACKLOG ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  channel ; 
 int close_cb_called ; 
 TYPE_1__ conn ; 
 int /*<<< orphan*/  connect_child_process_cb ; 
 int /*<<< orphan*/  ipc_on_connection_tcp_conn ; 
 int tcp_conn_read_cb_called ; 
 int tcp_conn_write_cb_called ; 
 int /*<<< orphan*/  tcp_server ; 
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
 int uv_tcp_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ipc_helper_tcp_connection(void) {
  /*
   * This is launched from test-ipc.c. stdin is a duplex channel
   * over which a handle will be transmitted.
   */

  int r;
  struct sockaddr_in addr;

  r = uv_pipe_init(uv_default_loop(), &channel, 1);
  ASSERT(r == 0);

  uv_pipe_open(&channel, 0);

  ASSERT(1 == uv_is_readable((uv_stream_t*) &channel));
  ASSERT(1 == uv_is_writable((uv_stream_t*) &channel));
  ASSERT(0 == uv_is_closing((uv_handle_t*) &channel));

  r = uv_tcp_init(uv_default_loop(), &tcp_server);
  ASSERT(r == 0);

  ASSERT(0 == uv_ip4_addr("0.0.0.0", TEST_PORT, &addr));

  r = uv_tcp_bind(&tcp_server, (const struct sockaddr*) &addr, 0);
  ASSERT(r == 0);

  r = uv_listen((uv_stream_t*)&tcp_server, BACKLOG, ipc_on_connection_tcp_conn);
  ASSERT(r == 0);

  /* Make a connection to the server */
  r = uv_tcp_init(uv_default_loop(), &conn.conn);
  ASSERT(r == 0);

  ASSERT(0 == uv_ip4_addr("127.0.0.1", TEST_PORT, &addr));

  r = uv_tcp_connect(&conn.conn_req,
                     (uv_tcp_t*) &conn.conn,
                     (const struct sockaddr*) &addr,
                     connect_child_process_cb);
  ASSERT(r == 0);

  r = uv_run(uv_default_loop(), UV_RUN_DEFAULT);
  ASSERT(r == 0);

  ASSERT(tcp_conn_read_cb_called == 1);
  ASSERT(tcp_conn_write_cb_called == 1);
  ASSERT(close_cb_called == 4);

  MAKE_VALGRIND_HAPPY();
  return 0;
}