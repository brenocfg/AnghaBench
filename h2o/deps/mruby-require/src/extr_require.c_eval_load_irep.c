#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct RProc {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  object_class; } ;
typedef  TYPE_1__ mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_PROC_SET_TARGET_CLASS (struct RProc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (TYPE_1__*,int) ; 
 int mrb_gc_arena_save (TYPE_1__*) ; 
 int /*<<< orphan*/  mrb_irep_decref (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RProc*) ; 
 struct RProc* mrb_proc_new (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_top_self (TYPE_1__*) ; 
 int /*<<< orphan*/  mrb_yield_with_class (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_stop_with_return (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
eval_load_irep(mrb_state *mrb, mrb_irep *irep)
{
  int ai;
  struct RProc *proc;

#ifdef USE_MRUBY_OLD_BYTE_CODE
  replace_stop_with_return(mrb, irep);
#endif
  proc = mrb_proc_new(mrb, irep);
  mrb_irep_decref(mrb, irep);
  MRB_PROC_SET_TARGET_CLASS(proc, mrb->object_class);

  ai = mrb_gc_arena_save(mrb);
  mrb_yield_with_class(mrb, mrb_obj_value(proc), 0, NULL, mrb_top_self(mrb), mrb->object_class);
  mrb_gc_arena_restore(mrb, ai);
}