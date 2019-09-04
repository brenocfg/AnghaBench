#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_thread_t ;
typedef  int /*<<< orphan*/  uv_process_t ;
struct TYPE_2__ {int /*<<< orphan*/  connect_req; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEST_PIPENAME_3 ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  connect_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ ctx ; 
 int /*<<< orphan*/  ipc_send_recv_helper_threadproc ; 
 int recv_cb_count ; 
 int /*<<< orphan*/  spawn_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int /*<<< orphan*/  uv_pipe_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ )) ; 
 int uv_pipe_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_sleep (int) ; 
 int uv_thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int uv_thread_join (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int run_test(int inprocess) {
  uv_process_t process;
  uv_thread_t tid;
  int r;

  if (inprocess) {
    r = uv_thread_create(&tid, ipc_send_recv_helper_threadproc, (void *) 42);
    ASSERT(r == 0);

    uv_sleep(1000);

    r = uv_pipe_init(uv_default_loop(), &ctx.channel, 1);
    ASSERT(r == 0);

    uv_pipe_connect(&ctx.connect_req, &ctx.channel, TEST_PIPENAME_3, connect_cb);
  } else {
    spawn_helper(&ctx.channel, &process, "ipc_send_recv_helper");

    connect_cb(&ctx.connect_req, 0);
  }

  r = uv_run(uv_default_loop(), UV_RUN_DEFAULT);
  ASSERT(r == 0);

  ASSERT(recv_cb_count == 2);

  if (inprocess) {
    r = uv_thread_join(&tid);
    ASSERT(r == 0);
  }

  return 0;
}