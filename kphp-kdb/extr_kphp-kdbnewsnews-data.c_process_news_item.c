#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tot_items; TYPE_2__* first; } ;
typedef  TYPE_1__ user_t ;
struct lev_news_item {int type; scalar_t__ item; scalar_t__ place; scalar_t__ owner; scalar_t__ user; scalar_t__ group; int /*<<< orphan*/  user_id; } ;
struct TYPE_7__ {scalar_t__ date; int type; scalar_t__ item; scalar_t__ place; scalar_t__ owner; scalar_t__ user; scalar_t__ group; int random_tag; struct TYPE_7__* prev; struct TYPE_7__* next; } ;
typedef  TYPE_2__ item_t ;

/* Variables and functions */
 int /*<<< orphan*/  UG_MODE ; 
 TYPE_1__* get_user_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  items_removed_in_process_new ; 
 int lrand48 () ; 
 scalar_t__ min_logevent_time ; 
 TYPE_2__* new_item () ; 
 scalar_t__ now ; 
 scalar_t__ remove_old_items (TYPE_1__*) ; 
 int /*<<< orphan*/  valid_type (int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int,scalar_t__,int) ; 

__attribute__((used)) static int process_news_item (struct lev_news_item *E) {
  if (now < min_logevent_time) {
    return 0;
  }
  user_t *U = get_user_f (E->user_id, 1);
  int t = E->type & 0xff;
  if (!U || !UG_MODE || !valid_type (t)) {
    return -1;
  }
  /*
  if ((t == 6 || E->user_id == 1034437) && verbosity > 2) {
     fprintf (stderr, "pos=%lld: process_news_item(%d,%d,%d,%d,%d,%d,%d,%d)\n", log_cur_pos(), E->user_id, now, t, E->user, E->group, E->owner, E->place, E->item);
  }
  */

  item_t *p, *q = U->first;

  if (q != (item_t *) U && q->date == now && q->type == t &&
      q->item == E->item && q->place == E->place && q->owner == E->owner &&
      q->user == E->user && q->group == E->group) {
    return 0;
  }

  p = new_item ();

  p->next = q;
  q->prev = p;
  p->prev = (item_t *) U;
  U->first = p;
  U->tot_items++;

  p->type = t;
  p->date = now;
  p->random_tag = lrand48() & 0x7fffffff;

  p->user = E->user;
  p->group = E->group;
  p->owner = E->owner;
  p->place = E->place;
  p->item = E->item;

  vkprintf (2, "new record stored: user_id=%d type=%d date=%d tag=%d\n", E->user_id, p->type, p->date, p->random_tag);

  items_removed_in_process_new += remove_old_items (U);

  return 1;
}