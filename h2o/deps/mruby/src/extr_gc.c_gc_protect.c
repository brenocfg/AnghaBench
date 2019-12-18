#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct RBasic {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  arena_err; } ;
typedef  TYPE_1__ mrb_state ;
struct TYPE_8__ {scalar_t__ arena_idx; int arena_capa; struct RBasic** arena; } ;
typedef  TYPE_2__ mrb_gc ;

/* Variables and functions */
 scalar_t__ MRB_GC_ARENA_SIZE ; 
 int /*<<< orphan*/  mrb_exc_raise (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_realloc (TYPE_1__*,struct RBasic**,int) ; 

__attribute__((used)) static void
gc_protect(mrb_state *mrb, mrb_gc *gc, struct RBasic *p)
{
#ifdef MRB_GC_FIXED_ARENA
  if (gc->arena_idx >= MRB_GC_ARENA_SIZE) {
    /* arena overflow error */
    gc->arena_idx = MRB_GC_ARENA_SIZE - 4; /* force room in arena */
    mrb_exc_raise(mrb, mrb_obj_value(mrb->arena_err));
  }
#else
  if (gc->arena_idx >= gc->arena_capa) {
    /* extend arena */
    gc->arena_capa = (int)(gc->arena_capa * 3 / 2);
    gc->arena = (struct RBasic**)mrb_realloc(mrb, gc->arena, sizeof(struct RBasic*)*gc->arena_capa);
  }
#endif
  gc->arena[gc->arena_idx++] = p;
}