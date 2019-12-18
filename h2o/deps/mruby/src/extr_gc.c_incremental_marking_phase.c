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
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_4__ {scalar_t__ gray_list; } ;
typedef  TYPE_1__ mrb_gc ;

/* Variables and functions */
 scalar_t__ gc_gray_mark (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static size_t
incremental_marking_phase(mrb_state *mrb, mrb_gc *gc, size_t limit)
{
  size_t tried_marks = 0;

  while (gc->gray_list && tried_marks < limit) {
    tried_marks += gc_gray_mark(mrb, gc, gc->gray_list);
  }

  return tried_marks;
}