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
typedef  int /*<<< orphan*/  uv_work_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  after_work_cb ; 
 int after_work_cb_count ; 
 int getpid () ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int uv_queue_work (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_cb ; 
 int work_cb_count ; 

__attribute__((used)) static void assert_run_work(uv_loop_t* const loop) {
  uv_work_t work_req;
  int r;

  ASSERT(work_cb_count == 0);
  ASSERT(after_work_cb_count == 0);
  printf("Queue in %d\n", getpid());
  r = uv_queue_work(loop, &work_req, work_cb, after_work_cb);
  ASSERT(r == 0);
  printf("Running in %d\n", getpid());
  uv_run(loop, UV_RUN_DEFAULT);

  ASSERT(work_cb_count == 1);
  ASSERT(after_work_cb_count == 1);

  /* cleanup  */
  work_cb_count = 0;
  after_work_cb_count = 0;
}