#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ size; TYPE_1__* e; struct TYPE_13__* next; } ;
typedef  TYPE_2__ segment ;
struct TYPE_14__ {scalar_t__ size; size_t capa; TYPE_1__** table; } ;
typedef  TYPE_3__ segindex ;
typedef  void* mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_15__ {scalar_t__ last_len; int /*<<< orphan*/  size; TYPE_2__* lastseg; TYPE_3__* index; } ;
typedef  TYPE_4__ htable ;
struct TYPE_12__ {void* val; void* key; } ;

/* Variables and functions */
 size_t HT_MASK (TYPE_3__*) ; 
 scalar_t__ UPPER_BOUND (size_t) ; 
 int /*<<< orphan*/  ht_compact (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ ht_hash_equal (int /*<<< orphan*/ *,TYPE_4__*,void*,void*) ; 
 size_t ht_hash_func (int /*<<< orphan*/ *,TYPE_4__*,void*) ; 
 scalar_t__ mrb_undef_p (void*) ; 
 TYPE_2__* segment_alloc (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
ht_index_put(mrb_state *mrb, htable *t, mrb_value key, mrb_value val)
{
  segindex *index = t->index;
  size_t k, sp, step = 0, mask;
  segment *seg;

  if (index->size >= UPPER_BOUND(index->capa)) {
    /* need to expand table */
    ht_compact(mrb, t);
    index = t->index;
  }
  mask = HT_MASK(index);
  sp = index->capa;
  k = ht_hash_func(mrb, t, key) & mask;
  while (index->table[k]) {
    mrb_value key2 = index->table[k]->key;
    if (mrb_undef_p(key2)) {
      if (sp == index->capa) sp = k;
    }
    else if (ht_hash_equal(mrb, t, key, key2)) {
      index->table[k]->val = val;
      return;
    }
    k = (k+(++step)) & mask;
  }
  if (sp < index->capa) {
    k = sp;
  }

  /* put the value at the last */
  seg = t->lastseg;
  if (t->last_len < seg->size) {
    index->table[k] = &seg->e[t->last_len++];
  }
  else {                        /* append a new segment */
    seg->next = segment_alloc(mrb, seg);
    seg = seg->next;
    seg->next = NULL;
    t->lastseg = seg;
    t->last_len = 1;
    index->table[k] = &seg->e[0];
  }
  index->table[k]->key = key;
  index->table[k]->val = val;
  index->size++;
  t->size++;
}