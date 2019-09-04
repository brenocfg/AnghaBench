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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int check_cb_called ; 
 int prepare_cb_called ; 
 scalar_t__ timer_cb_called ; 
 int /*<<< orphan*/  timer_handle ; 
 scalar_t__ uv_timer_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void timer_cb(uv_timer_t* handle) {
  ASSERT(0 == uv_timer_stop(&timer_handle));
  ASSERT(1 == prepare_cb_called);
  ASSERT(1 == check_cb_called);
  ASSERT(0 == timer_cb_called);
  timer_cb_called++;
}