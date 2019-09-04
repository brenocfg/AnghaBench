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
typedef  int /*<<< orphan*/  uv_pipe_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 int /*<<< orphan*/  do_writes_and_reads (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_parent_process () ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_pipe_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int uv_pipe_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_sleep (int) ; 

int ipc_helper_heavy_traffic_deadlock_bug(void) {
  uv_pipe_t pipe;
  int r;

  r = uv_pipe_init(uv_default_loop(), &pipe, 1);
  ASSERT(r == 0);
  r = uv_pipe_open(&pipe, 0);
  ASSERT(r == 0);

  notify_parent_process();
  do_writes_and_reads((uv_stream_t*) &pipe);
  uv_sleep(100);

  MAKE_VALGRIND_HAPPY();
  return 0;
}