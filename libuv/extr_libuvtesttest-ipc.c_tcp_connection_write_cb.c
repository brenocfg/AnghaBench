#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ handle; } ;
typedef  TYPE_1__ uv_write_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_5__ {int /*<<< orphan*/  conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  channel ; 
 int /*<<< orphan*/  close_cb ; 
 TYPE_3__ conn ; 
 int /*<<< orphan*/  tcp_conn_write_cb_called ; 
 int /*<<< orphan*/  tcp_server ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_connection_write_cb(uv_write_t* req, int status) {
  ASSERT((uv_handle_t*)&conn.conn == (uv_handle_t*)req->handle);
  uv_close((uv_handle_t*)req->handle, close_cb);
  uv_close((uv_handle_t*)&channel, close_cb);
  uv_close((uv_handle_t*)&tcp_server, close_cb);
  tcp_conn_write_cb_called++;
}