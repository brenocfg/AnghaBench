#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_11__ ;

/* Type definitions */
struct RBasic {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_26__ {struct TYPE_26__* next; void* old; struct RBasic* freelist; } ;
typedef  TYPE_3__ mrb_heap_page ;
struct TYPE_27__ {size_t live; size_t live_after_mark; TYPE_3__* sweeps; } ;
typedef  TYPE_4__ mrb_gc ;
typedef  void* mrb_bool ;
struct TYPE_23__ {scalar_t__ tt; } ;
struct TYPE_24__ {struct RBasic* next; } ;
struct TYPE_25__ {TYPE_11__ basic; TYPE_1__ free; } ;
struct TYPE_28__ {TYPE_2__ as; } ;
typedef  TYPE_5__ RVALUE ;

/* Variables and functions */
 void* FALSE ; 
 size_t MRB_HEAP_PAGE_SIZE ; 
 scalar_t__ MRB_TT_FREE ; 
 void* TRUE ; 
 scalar_t__ is_dead (TYPE_4__*,TYPE_11__*) ; 
 int /*<<< orphan*/  is_generational (TYPE_4__*) ; 
 scalar_t__ is_minor_gc (TYPE_4__*) ; 
 int /*<<< orphan*/  link_free_heap_page (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  obj_free (int /*<<< orphan*/ *,TYPE_11__*,void*) ; 
 TYPE_5__* objects (TYPE_3__*) ; 
 int /*<<< orphan*/  paint_partial_white (TYPE_4__*,TYPE_11__*) ; 
 int /*<<< orphan*/  unlink_free_heap_page (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  unlink_heap_page (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static size_t
incremental_sweep_phase(mrb_state *mrb, mrb_gc *gc, size_t limit)
{
  mrb_heap_page *page = gc->sweeps;
  size_t tried_sweep = 0;

  while (page && (tried_sweep < limit)) {
    RVALUE *p = objects(page);
    RVALUE *e = p + MRB_HEAP_PAGE_SIZE;
    size_t freed = 0;
    mrb_bool dead_slot = TRUE;
    mrb_bool full = (page->freelist == NULL);

    if (is_minor_gc(gc) && page->old) {
      /* skip a slot which doesn't contain any young object */
      p = e;
      dead_slot = FALSE;
    }
    while (p<e) {
      if (is_dead(gc, &p->as.basic)) {
        if (p->as.basic.tt != MRB_TT_FREE) {
          obj_free(mrb, &p->as.basic, FALSE);
          if (p->as.basic.tt == MRB_TT_FREE) {
            p->as.free.next = page->freelist;
            page->freelist = (struct RBasic*)p;
            freed++;
          }
          else {
            dead_slot = FALSE;
          }
        }
      }
      else {
        if (!is_generational(gc))
          paint_partial_white(gc, &p->as.basic); /* next gc target */
        dead_slot = FALSE;
      }
      p++;
    }

    /* free dead slot */
    if (dead_slot && freed < MRB_HEAP_PAGE_SIZE) {
      mrb_heap_page *next = page->next;

      unlink_heap_page(gc, page);
      unlink_free_heap_page(gc, page);
      mrb_free(mrb, page);
      page = next;
    }
    else {
      if (full && freed > 0) {
        link_free_heap_page(gc, page);
      }
      if (page->freelist == NULL && is_minor_gc(gc))
        page->old = TRUE;
      else
        page->old = FALSE;
      page = page->next;
    }
    tried_sweep += MRB_HEAP_PAGE_SIZE;
    gc->live -= freed;
    gc->live_after_mark -= freed;
  }
  gc->sweeps = page;
  return tried_sweep;
}