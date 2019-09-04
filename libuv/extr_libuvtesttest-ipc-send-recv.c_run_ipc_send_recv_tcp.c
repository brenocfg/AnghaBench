#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tcp; } ;
struct TYPE_4__ {int /*<<< orphan*/  tcp; } ;
struct TYPE_6__ {TYPE_2__ send2; TYPE_1__ send; int /*<<< orphan*/  expected_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  UV_TCP ; 
 TYPE_3__ ctx ; 
 int run_test (int) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int uv_tcp_bind (int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int run_ipc_send_recv_tcp(int inprocess) {
  struct sockaddr_in addr;
  int r;

  ASSERT(0 == uv_ip4_addr("127.0.0.1", TEST_PORT, &addr));

  ctx.expected_type = UV_TCP;

  r = uv_tcp_init(uv_default_loop(), &ctx.send.tcp);
  ASSERT(r == 0);

  r = uv_tcp_init(uv_default_loop(), &ctx.send2.tcp);
  ASSERT(r == 0);

  r = uv_tcp_bind(&ctx.send.tcp, (const struct sockaddr*) &addr, 0);
  ASSERT(r == 0);

  r = uv_tcp_bind(&ctx.send2.tcp, (const struct sockaddr*) &addr, 0);
  ASSERT(r == 0);

  r = run_test(inprocess);
  ASSERT(r == 0);

  MAKE_VALGRIND_HAPPY();
  return 0;
}