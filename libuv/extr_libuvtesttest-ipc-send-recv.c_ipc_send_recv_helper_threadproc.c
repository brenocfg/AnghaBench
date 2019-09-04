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
typedef  int /*<<< orphan*/  uv_loop_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int run_ipc_send_recv_helper (int /*<<< orphan*/ *,int) ; 
 int uv_loop_close (int /*<<< orphan*/ *) ; 
 int uv_loop_init (int /*<<< orphan*/ *) ; 

void ipc_send_recv_helper_threadproc(void* arg) {
  int r;
  uv_loop_t loop;

  r = uv_loop_init(&loop);
  ASSERT(r == 0);

  r = run_ipc_send_recv_helper(&loop, 1);
  ASSERT(r == 0);

  r = uv_loop_close(&loop);
  ASSERT(r == 0);
}