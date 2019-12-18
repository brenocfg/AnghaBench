#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  repeat; } ;
typedef  TYPE_1__ uv_timer_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */

void uv_timer_set_repeat(uv_timer_t* handle, uint64_t repeat) {
  handle->repeat = repeat;
}