#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uv_run_mode ;
struct TYPE_14__ {scalar_t__ stop_flag; } ;
typedef  TYPE_1__ uv_loop_t ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ UV_RUN_DEFAULT ; 
 scalar_t__ UV_RUN_NOWAIT ; 
 scalar_t__ UV_RUN_ONCE ; 
 scalar_t__ pGetQueuedCompletionStatusEx ; 
 int uv__loop_alive (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__poll (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__poll_wine (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__run_timers (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_backend_timeout (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_check_invoke (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_idle_invoke (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_prepare_invoke (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_process_endgames (TYPE_1__*) ; 
 int uv_process_reqs (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_update_time (TYPE_1__*) ; 

int uv_run(uv_loop_t *loop, uv_run_mode mode) {
  DWORD timeout;
  int r;
  int ran_pending;

  r = uv__loop_alive(loop);
  if (!r)
    uv_update_time(loop);

  while (r != 0 && loop->stop_flag == 0) {
    uv_update_time(loop);
    uv__run_timers(loop);

    ran_pending = uv_process_reqs(loop);
    uv_idle_invoke(loop);
    uv_prepare_invoke(loop);

    timeout = 0;
    if ((mode == UV_RUN_ONCE && !ran_pending) || mode == UV_RUN_DEFAULT)
      timeout = uv_backend_timeout(loop);

    if (pGetQueuedCompletionStatusEx)
      uv__poll(loop, timeout);
    else
      uv__poll_wine(loop, timeout);


    uv_check_invoke(loop);
    uv_process_endgames(loop);

    if (mode == UV_RUN_ONCE) {
      /* UV_RUN_ONCE implies forward progress: at least one callback must have
       * been invoked when it returns. uv__io_poll() can return without doing
       * I/O (meaning: no callbacks) when its timeout expires - which means we
       * have pending timers that satisfy the forward progress constraint.
       *
       * UV_RUN_NOWAIT makes no guarantees about progress so it's omitted from
       * the check.
       */
      uv__run_timers(loop);
    }

    r = uv__loop_alive(loop);
    if (mode == UV_RUN_ONCE || mode == UV_RUN_NOWAIT)
      break;
  }

  /* The if statement lets the compiler compile it to a conditional store.
   * Avoids dirtying a cache line.
   */
  if (loop->stop_flag != 0)
    loop->stop_flag = 0;

  return r;
}