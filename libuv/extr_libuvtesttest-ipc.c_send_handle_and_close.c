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
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  channel ; 
 int /*<<< orphan*/  closed_handle_write_cb ; 
 int /*<<< orphan*/  large_buf ; 
 int /*<<< orphan*/  tcp_server ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int uv_tcp_bind (int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_write2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_req ; 

__attribute__((used)) static void send_handle_and_close() {
  int r;
  struct sockaddr_in addr;

  r = uv_tcp_init(uv_default_loop(), &tcp_server);
  ASSERT(r == 0);

  ASSERT(0 == uv_ip4_addr("0.0.0.0", TEST_PORT, &addr));

  r = uv_tcp_bind(&tcp_server, (const struct sockaddr*) &addr, 0);
  ASSERT(r == 0);

  r = uv_write2(&write_req,
                (uv_stream_t*)&channel,
                &large_buf,
                1,
                (uv_stream_t*)&tcp_server,
                closed_handle_write_cb);
  ASSERT(r == 0);

  uv_close((uv_handle_t*)&tcp_server, NULL);
}