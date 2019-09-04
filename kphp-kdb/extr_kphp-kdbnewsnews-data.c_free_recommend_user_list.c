#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ total_items; TYPE_2__* last; TYPE_2__* first; } ;
typedef  TYPE_1__ recommend_user_t ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_2__ recommend_item_t ;

/* Variables and functions */
 int RECOMMEND_MODE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_recommend_item (TYPE_2__*) ; 

__attribute__((used)) static void free_recommend_user_list (recommend_user_t *U) {
  assert (RECOMMEND_MODE);
  recommend_item_t *p = U->first, *q;
  while (p != (recommend_item_t *) U) {
    q = p->next;
    U->total_items--;
    assert (U->total_items >= 0);
    free_recommend_item (p);
    p = q;
  }
  assert (!U->total_items);
  U->first = U->last = (recommend_item_t *) U;
}