#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* key; struct TYPE_4__* next; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ segment ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  scalar_t__ mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_bool ;
struct TYPE_5__ {size_t last_len; TYPE_1__* rootseg; } ;
typedef  TYPE_2__ iv_tbl ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t MRB_IV_SEGMENT_SIZE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static mrb_bool
iv_get(mrb_state *mrb, iv_tbl *t, mrb_sym sym, mrb_value *vp)
{
  segment *seg;
  size_t i;

  if (t == NULL) return FALSE;
  seg = t->rootseg;
  while (seg) {
    for (i=0; i<MRB_IV_SEGMENT_SIZE; i++) {
      mrb_sym key = seg->key[i];

      if (!seg->next && i >= t->last_len) {
        return FALSE;
      }
      if (key == sym) {
        if (vp) *vp = seg->val[i];
        return TRUE;
      }
    }
    seg = seg->next;
  }
  return FALSE;
}