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
struct TYPE_5__ {int /*<<< orphan*/  pipe; } ;
struct TYPE_4__ {int /*<<< orphan*/  pipe; } ;
struct TYPE_6__ {TYPE_2__ send2; TYPE_1__ send; int /*<<< orphan*/  expected_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 int /*<<< orphan*/  TEST_PIPENAME ; 
 int /*<<< orphan*/  TEST_PIPENAME_2 ; 
 int /*<<< orphan*/  UV_NAMED_PIPE ; 
 TYPE_3__ ctx ; 
 int run_test (int) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_pipe_bind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_pipe_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int run_ipc_send_recv_pipe(int inprocess) {
  int r;

  ctx.expected_type = UV_NAMED_PIPE;

  r = uv_pipe_init(uv_default_loop(), &ctx.send.pipe, 1);
  ASSERT(r == 0);

  r = uv_pipe_bind(&ctx.send.pipe, TEST_PIPENAME);
  ASSERT(r == 0);

  r = uv_pipe_init(uv_default_loop(), &ctx.send2.pipe, 1);
  ASSERT(r == 0);

  r = uv_pipe_bind(&ctx.send2.pipe, TEST_PIPENAME_2);
  ASSERT(r == 0);

  r = run_test(inprocess);
  ASSERT(r == 0);

  MAKE_VALGRIND_HAPPY();
  return 0;
}