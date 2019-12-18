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
struct TYPE_6__ {scalar_t__ item_id; } ;
typedef  TYPE_2__ item_t ;
struct TYPE_7__ {scalar_t__ item_id; int cur_y; size_t sp; int tag_word; int cur_y1; TYPE_2__* cur; TYPE_1__** TS; TYPE_2__* cur1; TYPE_2__* cur0; } ;
typedef  TYPE_3__ iheap_en_t ;
struct TYPE_5__ {int y; } ;

/* Variables and functions */
 scalar_t__ MAX_ITEM_ID ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ihe_load (iheap_en_t *A) {
  item_t *I0 = A->cur0, *I1 = A->cur1;
  if (unlikely(!I0 && !I1)) {
    A->item_id = MAX_ITEM_ID;
    A->cur = 0;
    A->cur_y = 0;
    return 0;
  }
  if (unlikely(!I1)) {
    A->cur = I0;
    assert (A->sp >= 0);
    A->cur_y = A->TS[A->sp]->y | A->tag_word;
    A->item_id = I0->item_id;
  } else if (!I0) {
    A->cur = I1;
    A->cur_y = A->cur_y1 | A->tag_word;
    A->item_id = I1->item_id;
  } else if (unlikely(I0->item_id < I1->item_id)) {
    A->cur = I0;
    A->cur_y = A->TS[A->sp]->y | A->tag_word;
    A->item_id = I0->item_id;
  } else {
    A->cur = I1;
    A->cur_y = A->cur_y1 | A->tag_word;
    A->item_id = I1->item_id;
  }
  return 1;
}