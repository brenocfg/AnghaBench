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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  done_cb ; 
 scalar_t__ pause_reqs ; 
 scalar_t__ pause_sems ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 
 int /*<<< orphan*/ * uv_default_loop () ; 
 scalar_t__ uv_queue_work (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_sem_init (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_cb ; 

__attribute__((used)) static void saturate_threadpool(void) {
  uv_loop_t* loop;
  char buf[64];
  size_t i;

  snprintf(buf,
           sizeof(buf),
           "UV_THREADPOOL_SIZE=%lu",
           (unsigned long)ARRAY_SIZE(pause_reqs));
  putenv(buf);

  loop = uv_default_loop();
  for (i = 0; i < ARRAY_SIZE(pause_reqs); i += 1) {
    ASSERT(0 == uv_sem_init(pause_sems + i, 0));
    ASSERT(0 == uv_queue_work(loop, pause_reqs + i, work_cb, done_cb));
  }
}