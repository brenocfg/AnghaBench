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
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  connection_cb ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int uv_listen (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int uv_tcp_bind (int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void start_server(uv_loop_t* loop, uv_tcp_t* handle) {
  struct sockaddr_in addr;
  int r;

  ASSERT(0 == uv_ip4_addr("127.0.0.1", TEST_PORT, &addr));

  r = uv_tcp_init(loop, handle);
  ASSERT(r == 0);

  r = uv_tcp_bind(handle, (const struct sockaddr*) &addr, 0);
  ASSERT(r == 0);

  r = uv_listen((uv_stream_t*)handle, 128, connection_cb);
  ASSERT(r == 0);

  uv_unref((uv_handle_t*)handle);
}