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
typedef  int /*<<< orphan*/  uv_udp_recv_cb ;
typedef  int /*<<< orphan*/  uv_buf_t ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  alloc_cb ; 
 int /*<<< orphan*/  client ; 
 int close_cb_called ; 
 scalar_t__ recv_cb_called ; 
 int /*<<< orphan*/  req_ ; 
 int /*<<< orphan*/  send_cb ; 
 scalar_t__ send_cb_called ; 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  timeout_cb ; 
 int /*<<< orphan*/  uv_buf_init (char*,int) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 scalar_t__ uv_ip6_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in6*) ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_timer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int uv_udp_bind (int /*<<< orphan*/ *,struct sockaddr const*,int) ; 
 int uv_udp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_udp_recv_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_udp_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct sockaddr const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_test(uv_udp_recv_cb recv_cb, int bind_flags) {
  struct sockaddr_in6 addr6;
  struct sockaddr_in addr;
  uv_buf_t buf;
  int r;

  ASSERT(0 == uv_ip6_addr("::0", TEST_PORT, &addr6));

  r = uv_udp_init(uv_default_loop(), &server);
  ASSERT(r == 0);

  r = uv_udp_bind(&server, (const struct sockaddr*) &addr6, bind_flags);
  ASSERT(r == 0);

  r = uv_udp_recv_start(&server, alloc_cb, recv_cb);
  ASSERT(r == 0);

  r = uv_udp_init(uv_default_loop(), &client);
  ASSERT(r == 0);

  buf = uv_buf_init("PING", 4);
  ASSERT(0 == uv_ip4_addr("127.0.0.1", TEST_PORT, &addr));

  r = uv_udp_send(&req_,
                  &client,
                  &buf,
                  1,
                  (const struct sockaddr*) &addr,
                  send_cb);
  ASSERT(r == 0);

  r = uv_timer_init(uv_default_loop(), &timeout);
  ASSERT(r == 0);

  r = uv_timer_start(&timeout, timeout_cb, 500, 0);
  ASSERT(r == 0);

  ASSERT(close_cb_called == 0);
  ASSERT(send_cb_called == 0);
  ASSERT(recv_cb_called == 0);

  uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  ASSERT(close_cb_called == 3);

  MAKE_VALGRIND_HAPPY();
}