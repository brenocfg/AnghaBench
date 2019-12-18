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
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_EINVAL ; 
 scalar_t__ UV_ENOTCONN ; 
 int /*<<< orphan*/  close_cb ; 
 int shutdown_before_close ; 
 int /*<<< orphan*/  shutdown_cb ; 
 int /*<<< orphan*/  shutdown_req ; 
 int /*<<< orphan*/  tcp_server ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_shutdown (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_tcp_close_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_close(uv_tcp_t* handle) {
  if (shutdown_before_close == 1) {
    ASSERT(0 == uv_shutdown(&shutdown_req, (uv_stream_t*) handle, shutdown_cb));
    ASSERT(UV_EINVAL == uv_tcp_close_reset(handle, close_cb));
  } else {
    ASSERT(0 == uv_tcp_close_reset(handle, close_cb));
    ASSERT(UV_ENOTCONN == uv_shutdown(&shutdown_req, (uv_stream_t*) handle, shutdown_cb));
  }

  uv_close((uv_handle_t*) &tcp_server, NULL);
}