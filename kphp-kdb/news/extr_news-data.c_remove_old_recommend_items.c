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
struct TYPE_5__ {int total_items; TYPE_2__* last; } ;
typedef  TYPE_1__ recommend_user_t ;
struct TYPE_6__ {int date; struct TYPE_6__* next; struct TYPE_6__* prev; } ;
typedef  TYPE_2__ recommend_item_t ;

/* Variables and functions */
 int MAX_USER_ITEMS ; 
 int RECOMMEND_MODE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_recommend_item (TYPE_2__*) ; 
 int max_news_days ; 
 int now ; 

__attribute__((used)) static int remove_old_recommend_items (recommend_user_t *U) {
  assert (RECOMMEND_MODE);
  int x = U->total_items, y;
  if (!x) {
    return 0;
  }
  y = now - (max_news_days + 1) * 86400;

  recommend_item_t *p = U->last, *q;
  const int old_total_items = x;
  while (p != (recommend_item_t *) U && (x > MAX_USER_ITEMS || p->date <= y)) {
    q = p->prev;
    free_recommend_item (p);
    x--;
    p = q;
  }
  U->last = p;
  p->next = (recommend_item_t *) U;
  U->total_items = x;
  assert (U->total_items >= 0);
  return old_total_items - x;
}