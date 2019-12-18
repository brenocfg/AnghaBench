#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_tcp_t ;
struct TYPE_5__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/ * close_server_conn_cb ; 
 int local_conn_accepted ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  tcp_server ; 
 int uv_accept (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_connection(uv_stream_t* server, int status) {
  uv_tcp_t* conn;
  int r;

  if (!local_conn_accepted) {
    /* Accept the connection and close it.  Also and close the server. */
    ASSERT(status == 0);
    ASSERT((uv_stream_t*)&tcp_server == server);

    conn = malloc(sizeof(*conn));
    ASSERT(conn);
    r = uv_tcp_init(server->loop, conn);
    ASSERT(r == 0);

    r = uv_accept(server, (uv_stream_t*)conn);
    ASSERT(r == 0);

    uv_close((uv_handle_t*)conn, close_server_conn_cb);
    uv_close((uv_handle_t*)server, NULL);
    local_conn_accepted = 1;
  }
}