#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t size; struct TYPE_6__* next; TYPE_1__* e; } ;
typedef  TYPE_2__ segment ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;
typedef  scalar_t__ (* mrb_hash_foreach_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;
struct TYPE_7__ {size_t last_len; TYPE_2__* rootseg; } ;
typedef  TYPE_3__ htable ;
struct TYPE_5__ {int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 scalar_t__ mrb_undef_p (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
ht_foreach(mrb_state *mrb, htable *t, mrb_hash_foreach_func *func, void *p)
{
  segment *seg;
  mrb_int i;

  if (t == NULL) return;
  seg = t->rootseg;
  while (seg) {
    for (i=0; i<seg->size; i++) {
      /* no value in last segment after last_len */
      if (!seg->next && i >= t->last_len) {
        return;
      }
      if (mrb_undef_p(seg->e[i].key)) continue;
      if ((*func)(mrb, seg->e[i].key, seg->e[i].val, p) != 0)
        return;
    }
    seg = seg->next;
  }
}