#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_7__ {int /*<<< orphan*/ * gray_list; int /*<<< orphan*/  atomic_gray_list; int /*<<< orphan*/  generational; } ;
typedef  TYPE_1__ mrb_gc ;
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MRB_GC_STATE_ROOT ; 
 int /*<<< orphan*/  incremental_gc_until (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_generational (TYPE_1__*) ; 
 scalar_t__ is_major_gc (TYPE_1__*) ; 
 int /*<<< orphan*/  mrb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_incremental_sweep (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
clear_all_old(mrb_state *mrb, mrb_gc *gc)
{
  mrb_bool origin_mode = gc->generational;

  mrb_assert(is_generational(gc));
  if (is_major_gc(gc)) {
    /* finish the half baked GC */
    incremental_gc_until(mrb, gc, MRB_GC_STATE_ROOT);
  }

  /* Sweep the dead objects, then reset all the live objects
   * (including all the old objects, of course) to white. */
  gc->generational = FALSE;
  prepare_incremental_sweep(mrb, gc);
  incremental_gc_until(mrb, gc, MRB_GC_STATE_ROOT);
  gc->generational = origin_mode;

  /* The gray objects have already been painted as white */
  gc->atomic_gray_list = gc->gray_list = NULL;
}