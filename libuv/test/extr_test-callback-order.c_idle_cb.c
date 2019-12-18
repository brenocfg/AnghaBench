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
typedef  int /*<<< orphan*/  uv_idle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ idle_cb_called ; 
 scalar_t__ timer_cb_called ; 
 int /*<<< orphan*/  uv_idle_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idle_cb(uv_idle_t* handle) {
  ASSERT(idle_cb_called == 0);
  ASSERT(timer_cb_called == 0);
  uv_idle_stop(handle);
  idle_cb_called++;
}