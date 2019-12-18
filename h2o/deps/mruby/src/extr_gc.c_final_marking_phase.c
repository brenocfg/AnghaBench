#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct RBasic {int dummy; } ;
struct TYPE_10__ {scalar_t__ exc; int /*<<< orphan*/  root_c; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ mrb_state ;
struct TYPE_11__ {int arena_idx; int /*<<< orphan*/ * gray_list; int /*<<< orphan*/ * atomic_gray_list; struct RBasic** arena; } ;
typedef  TYPE_2__ mrb_gc ;

/* Variables and functions */
 int /*<<< orphan*/  gc_mark_gray_list (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mark_context (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_mark (TYPE_1__*,struct RBasic*) ; 
 int /*<<< orphan*/  mrb_gc_mark_gv (TYPE_1__*) ; 

__attribute__((used)) static void
final_marking_phase(mrb_state *mrb, mrb_gc *gc)
{
  int i, e;

  /* mark arena */
  for (i=0,e=gc->arena_idx; i<e; i++) {
    mrb_gc_mark(mrb, gc->arena[i]);
  }
  mrb_gc_mark_gv(mrb);
  mark_context(mrb, mrb->c);
  mark_context(mrb, mrb->root_c);
  mrb_gc_mark(mrb, (struct RBasic*)mrb->exc);
  gc_mark_gray_list(mrb, gc);
  mrb_assert(gc->gray_list == NULL);
  gc->gray_list = gc->atomic_gray_list;
  gc->atomic_gray_list = NULL;
  gc_mark_gray_list(mrb, gc);
  mrb_assert(gc->gray_list == NULL);
}