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
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_check_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int IDLE_COUNT ; 
 int ITERATIONS ; 
 int /*<<< orphan*/  check_cb_called ; 
 int /*<<< orphan*/  check_close_cb ; 
 int /*<<< orphan*/  check_handle ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  idle_1_cb ; 
 int /*<<< orphan*/  idle_1_close_cb ; 
 int /*<<< orphan*/ * idle_1_handles ; 
 int /*<<< orphan*/  idle_2_close_cb ; 
 int /*<<< orphan*/  idle_2_handle ; 
 scalar_t__ idle_2_is_active ; 
 int /*<<< orphan*/  idles_1_active ; 
 int loop_iteration ; 
 int /*<<< orphan*/  prepare_1_close_cb ; 
 int /*<<< orphan*/  prepare_1_handle ; 
 int /*<<< orphan*/  prepare_2_close_cb ; 
 int /*<<< orphan*/  prepare_2_handle ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_idle_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_cb(uv_check_t* handle) {
  int i, r;

  fprintf(stderr, "%s", "CHECK_CB\n");
  fflush(stderr);
  ASSERT(handle == &check_handle);

  if (loop_iteration < ITERATIONS) {
    /* Make some idle watchers active */
    for (i = 0; i < 1 + (loop_iteration % IDLE_COUNT); i++) {
      r = uv_idle_start(&idle_1_handles[i], idle_1_cb);
      ASSERT(r == 0);
      idles_1_active++;
    }

  } else {
    /* End of the test - close all handles */
    uv_close((uv_handle_t*)&prepare_1_handle, prepare_1_close_cb);
    uv_close((uv_handle_t*)&check_handle, check_close_cb);
    uv_close((uv_handle_t*)&prepare_2_handle, prepare_2_close_cb);

    for (i = 0; i < IDLE_COUNT; i++) {
      uv_close((uv_handle_t*)&idle_1_handles[i], idle_1_close_cb);
    }

    /* This handle is closed/recreated every time, close it only if it is
     * active. */
    if (idle_2_is_active) {
      uv_close((uv_handle_t*)&idle_2_handle, idle_2_close_cb);
    }
  }

  check_cb_called++;
}