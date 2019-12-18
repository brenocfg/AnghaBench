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
struct TYPE_4__ {scalar_t__ signum; int flags; scalar_t__ loop; } ;
typedef  TYPE_1__ uv_signal_t ;

/* Variables and functions */
 int UV_SIGNAL_ONE_SHOT ; 

__attribute__((used)) static int uv__signal_compare(uv_signal_t* w1, uv_signal_t* w2) {
  int f1;
  int f2;
  /* Compare signums first so all watchers with the same signnum end up
   * adjacent.
   */
  if (w1->signum < w2->signum) return -1;
  if (w1->signum > w2->signum) return 1;

  /* Handlers without UV_SIGNAL_ONE_SHOT set will come first, so if the first
   * handler returned is a one-shot handler, the rest will be too.
   */
  f1 = w1->flags & UV_SIGNAL_ONE_SHOT;
  f2 = w2->flags & UV_SIGNAL_ONE_SHOT;
  if (f1 < f2) return -1;
  if (f1 > f2) return 1;

  /* Sort by loop pointer, so we can easily look up the first item after
   * { .signum = x, .loop = NULL }.
   */
  if (w1->loop < w2->loop) return -1;
  if (w1->loop > w2->loop) return 1;

  if (w1 < w2) return -1;
  if (w1 > w2) return 1;

  return 0;
}