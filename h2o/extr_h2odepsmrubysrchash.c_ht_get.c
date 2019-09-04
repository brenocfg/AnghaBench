#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t size; struct TYPE_8__* next; TYPE_1__* e; } ;
typedef  TYPE_2__ segment ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;
typedef  int /*<<< orphan*/  mrb_bool ;
struct TYPE_9__ {size_t last_len; TYPE_2__* rootseg; scalar_t__ index; } ;
typedef  TYPE_3__ htable ;
struct TYPE_7__ {int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ht_hash_equal (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ht_index_get (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_undef_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_bool
ht_get(mrb_state *mrb, htable *t, mrb_value key, mrb_value *vp)
{
  segment *seg;
  mrb_int i;

  if (t == NULL) return FALSE;
  if (t->index) {
    return ht_index_get(mrb, t, key, vp);
  }

  seg = t->rootseg;
  while (seg) {
    for (i=0; i<seg->size; i++) {
      mrb_value k = seg->e[i].key;

      if (!seg->next && i >= t->last_len) {
        return FALSE;
      }
      if (mrb_undef_p(k)) continue;
      if (ht_hash_equal(mrb, t, k, key)) {
        if (vp) *vp = seg->e[i].val;
        return TRUE;
      }
    }
    seg = seg->next;
  }
  return FALSE;
}