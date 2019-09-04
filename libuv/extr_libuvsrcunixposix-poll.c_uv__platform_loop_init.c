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
struct TYPE_3__ {scalar_t__ poll_fds_iterating; scalar_t__ poll_fds_size; scalar_t__ poll_fds_used; int /*<<< orphan*/ * poll_fds; } ;
typedef  TYPE_1__ uv_loop_t ;

/* Variables and functions */

int uv__platform_loop_init(uv_loop_t* loop) {
  loop->poll_fds = NULL;
  loop->poll_fds_used = 0;
  loop->poll_fds_size = 0;
  loop->poll_fds_iterating = 0;
  return 0;
}