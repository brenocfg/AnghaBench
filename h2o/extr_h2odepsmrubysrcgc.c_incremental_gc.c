#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_9__ {int state; int /*<<< orphan*/  gray_list; } ;
typedef  TYPE_1__ mrb_gc ;

/* Variables and functions */
#define  MRB_GC_STATE_MARK 130 
#define  MRB_GC_STATE_ROOT 129 
#define  MRB_GC_STATE_SWEEP 128 
 int /*<<< orphan*/  final_marking_phase (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  flip_white_part (TYPE_1__*) ; 
 size_t incremental_marking_phase (int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 
 size_t incremental_sweep_phase (int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  mrb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_incremental_sweep (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  root_scan_phase (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static size_t
incremental_gc(mrb_state *mrb, mrb_gc *gc, size_t limit)
{
  switch (gc->state) {
  case MRB_GC_STATE_ROOT:
    root_scan_phase(mrb, gc);
    gc->state = MRB_GC_STATE_MARK;
    flip_white_part(gc);
    return 0;
  case MRB_GC_STATE_MARK:
    if (gc->gray_list) {
      return incremental_marking_phase(mrb, gc, limit);
    }
    else {
      final_marking_phase(mrb, gc);
      prepare_incremental_sweep(mrb, gc);
      return 0;
    }
  case MRB_GC_STATE_SWEEP: {
     size_t tried_sweep = 0;
     tried_sweep = incremental_sweep_phase(mrb, gc, limit);
     if (tried_sweep == 0)
       gc->state = MRB_GC_STATE_ROOT;
     return tried_sweep;
  }
  default:
    /* unknown state */
    mrb_assert(0);
    return 0;
  }
}