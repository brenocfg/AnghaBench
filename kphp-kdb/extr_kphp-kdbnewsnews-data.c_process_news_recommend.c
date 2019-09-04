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
struct lev_news_recommend {int type; int /*<<< orphan*/  action; int /*<<< orphan*/  item_creation_time; int /*<<< orphan*/  place; int /*<<< orphan*/  owner; int /*<<< orphan*/  user_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  total_items; TYPE_2__* first; } ;
typedef  TYPE_1__ recommend_user_t ;
struct TYPE_6__ {int type; int /*<<< orphan*/  action; scalar_t__ date; int /*<<< orphan*/  item_creation_time; int /*<<< orphan*/  place; int /*<<< orphan*/  owner; struct TYPE_6__* prev; struct TYPE_6__* next; } ;
typedef  TYPE_2__ recommend_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  RECOMMEND_MODE ; 
 scalar_t__ get_user_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  items_removed_in_process_new ; 
 scalar_t__ min_logevent_time ; 
 TYPE_2__* new_recommend_item () ; 
 scalar_t__ now ; 
 scalar_t__ remove_old_recommend_items (TYPE_1__*) ; 
 int /*<<< orphan*/  valid_type (int) ; 

__attribute__((used)) static int process_news_recommend (struct lev_news_recommend *E) {
  if (now < min_logevent_time) {
    return 0;
  }
  recommend_user_t *U = (recommend_user_t *) get_user_f (E->user_id, 1);
  int t = E->type & 0xff;
  if (!U || !RECOMMEND_MODE || !valid_type (t)) {
    return -1;
  }

  recommend_item_t *p, *q = U->first;

  p = new_recommend_item ();

  p->next = q;
  q->prev = p;
  p->prev = (recommend_item_t *) U;
  U->first = p;
  U->total_items++;

  p->owner = E->owner;
  p->place = E->place;
  //p->item = E->item;
  p->item_creation_time = E->item_creation_time;
  p->date = now;
  p->type = t;
  p->action = E->action;

  items_removed_in_process_new += remove_old_recommend_items (U);

  return 1;
}