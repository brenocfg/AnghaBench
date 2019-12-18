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
struct lev_news_comment {int type; int /*<<< orphan*/  item; int /*<<< orphan*/  group; int /*<<< orphan*/  user; int /*<<< orphan*/  place; int /*<<< orphan*/  owner; } ;
struct TYPE_6__ {int /*<<< orphan*/  place; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/  tot_comments; TYPE_2__* first; } ;
typedef  TYPE_1__ place_t ;
struct TYPE_7__ {int random_tag; scalar_t__ date; int /*<<< orphan*/  item; int /*<<< orphan*/  group; int /*<<< orphan*/  user; struct TYPE_7__* prev; struct TYPE_7__* next; } ;
typedef  TYPE_2__ comment_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_MODE ; 
 int /*<<< orphan*/  check_obj (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_place_f (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ index_mode ; 
 int /*<<< orphan*/  items_removed_in_process_new ; 
 int lrand48 () ; 
 scalar_t__ min_logevent_time ; 
 TYPE_2__* new_comment () ; 
 scalar_t__ now ; 
 scalar_t__ remove_old_comments (TYPE_1__*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int process_news_comment (struct lev_news_comment *E) {
  if (now < min_logevent_time) {
    return 0;
  }
  int t = E->type & 0xff;
  if (!check_obj (t, E->owner, E->place) || !COMM_MODE) {
    return -1;
  }
  if (index_mode) {
    return 0;
  }

  place_t *V = get_place_f (t, E->owner, E->place, 1);

  comment_t *p = new_comment (), *q = V->first;

  p->next = q;
  q->prev = p;
  p->prev = (comment_t *) V;
  V->first = p;
  V->tot_comments++;

  p->date = now;
  p->random_tag = lrand48() & 0x7fffffff;

  p->user = E->user;
  p->group = E->group;
  p->item = E->item;

  vkprintf (2, "new comment stored: place=%d:%d:%d item=%d date=%d tag=%d\n", V->type, V->owner, V->place, p->item, p->date, p->random_tag);

  items_removed_in_process_new += remove_old_comments (V);
  return 1;
}