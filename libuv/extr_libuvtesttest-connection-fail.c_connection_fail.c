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
typedef  int /*<<< orphan*/  uv_connect_cb ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int close_cb_calls ; 
 int connect_cb_calls ; 
 int /*<<< orphan*/  req ; 
 int /*<<< orphan*/  tcp ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_tcp_bind (int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void connection_fail(uv_connect_cb connect_cb) {
  struct sockaddr_in client_addr, server_addr;
  int r;

  ASSERT(0 == uv_ip4_addr("0.0.0.0", 0, &client_addr));

  /* There should be no servers listening on this port. */
  ASSERT(0 == uv_ip4_addr("127.0.0.1", TEST_PORT, &server_addr));

  /* Try to connect to the server and do NUM_PINGS ping-pongs. */
  r = uv_tcp_init(uv_default_loop(), &tcp);
  ASSERT(!r);

  /* We are never doing multiple reads/connects at a time anyway. so these
   * handles can be pre-initialized. */
  ASSERT(0 == uv_tcp_bind(&tcp, (const struct sockaddr*) &client_addr, 0));

  r = uv_tcp_connect(&req,
                     &tcp,
                     (const struct sockaddr*) &server_addr,
                     connect_cb);
  ASSERT(!r);

  uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  ASSERT(connect_cb_calls == 1);
  ASSERT(close_cb_calls == 1);
}