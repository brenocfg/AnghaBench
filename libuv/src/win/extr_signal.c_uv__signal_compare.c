#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ signum; scalar_t__ loop; } ;
typedef  TYPE_1__ uv_signal_t ;

/* Variables and functions */

__attribute__((used)) static int uv__signal_compare(uv_signal_t* w1, uv_signal_t* w2) {
  /* Compare signums first so all watchers with the same signnum end up
   * adjacent. */
  if (w1->signum < w2->signum) return -1;
  if (w1->signum > w2->signum) return 1;

  /* Sort by loop pointer, so we can easily look up the first item after
   * { .signum = x, .loop = NULL }. */
  if ((uintptr_t) w1->loop < (uintptr_t) w2->loop) return -1;
  if ((uintptr_t) w1->loop > (uintptr_t) w2->loop) return 1;

  if ((uintptr_t) w1 < (uintptr_t) w2) return -1;
  if ((uintptr_t) w1 > (uintptr_t) w2) return 1;

  return 0;
}