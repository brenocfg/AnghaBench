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
 scalar_t__ NUM_TICKS ; 
 scalar_t__ ticks ; 
 int /*<<< orphan*/  uv_idle_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idle_cb(uv_idle_t* handle) {
  if (++ticks == NUM_TICKS)
    uv_idle_stop(handle);
}