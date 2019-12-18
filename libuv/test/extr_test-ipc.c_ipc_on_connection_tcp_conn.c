#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_tcp_t ;
struct TYPE_8__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  channel ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  conn_notify_req ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  on_read_alloc ; 
 int /*<<< orphan*/  on_tcp_child_process_read ; 
 int /*<<< orphan*/  tcp_server ; 
 int uv_accept (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  uv_buf_init (char*,int) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_read_start (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_write2 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipc_on_connection_tcp_conn(uv_stream_t* server, int status) {
  int r;
  uv_buf_t buf;
  uv_tcp_t* conn;

  ASSERT(status == 0);
  ASSERT((uv_stream_t*)&tcp_server == server);

  conn = malloc(sizeof(*conn));
  ASSERT(conn);

  r = uv_tcp_init(server->loop, conn);
  ASSERT(r == 0);

  r = uv_accept(server, (uv_stream_t*)conn);
  ASSERT(r == 0);

  /* Send the accepted connection to the other process */
  buf = uv_buf_init("hello\n", 6);
  r = uv_write2(&conn_notify_req, (uv_stream_t*)&channel, &buf, 1,
    (uv_stream_t*)conn, NULL);
  ASSERT(r == 0);

  r = uv_read_start((uv_stream_t*) conn,
                    on_read_alloc,
                    on_tcp_child_process_read);
  ASSERT(r == 0);

  uv_close((uv_handle_t*)conn, close_cb);
}