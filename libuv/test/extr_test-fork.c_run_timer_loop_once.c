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
typedef  int /*<<< orphan*/  uv_timer_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  timer_cb ; 
 int timer_cb_called ; 
 int /*<<< orphan*/ * uv_default_loop () ; 
 scalar_t__ uv_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_timer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_timer_loop_once(void) {
  uv_loop_t* loop;
  uv_timer_t timer_handle;

  loop = uv_default_loop();

  timer_cb_called = 0; /* Reset for the child. */

  ASSERT(0 == uv_timer_init(loop, &timer_handle));
  ASSERT(0 == uv_timer_start(&timer_handle, timer_cb, 1, 0));
  ASSERT(0 == uv_run(loop, UV_RUN_DEFAULT));
  ASSERT(1 == timer_cb_called);
}