#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__** table; } ;
typedef  TYPE_2__ segindex ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_bool ;
struct TYPE_10__ {TYPE_2__* index; } ;
typedef  TYPE_3__ htable ;
struct TYPE_8__ {int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t HT_MASK (TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ht_hash_equal (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ht_hash_func (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_undef_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_bool
ht_index_get(mrb_state *mrb, htable *t, mrb_value key, mrb_value *vp)
{
  segindex *index = t->index;
  size_t mask = HT_MASK(index);
  size_t k = ht_hash_func(mrb, t, key) & mask;
  size_t step = 0;

  while (index->table[k]) {
    mrb_value key2 = index->table[k]->key;
    if (!mrb_undef_p(key2) && ht_hash_equal(mrb, t, key, key2)) {
      if (vp) *vp = index->table[k]->val;
      return TRUE;
    }
    k = (k+(++step)) & mask;
  }
  return FALSE;
}