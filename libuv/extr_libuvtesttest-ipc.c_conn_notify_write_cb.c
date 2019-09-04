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
typedef  int /*<<< orphan*/  uv_write_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  channel ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  tcp_server ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void conn_notify_write_cb(uv_write_t* req, int status) {
  uv_close((uv_handle_t*)&tcp_server, close_cb);
  uv_close((uv_handle_t*)&channel, close_cb);
}