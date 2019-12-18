#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lev_news_item {int user; int group; int owner; int place; int item; int /*<<< orphan*/  user_id; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ LEV_NEWS_ITEM ; 
 int /*<<< orphan*/  UG_MODE ; 
 struct lev_news_item* alloc_log_event (scalar_t__,int,int) ; 
 scalar_t__ conv_uid (int) ; 
 int process_news_item (struct lev_news_item*) ; 
 int /*<<< orphan*/  valid_type (int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int do_process_news_item (int user_id, int type, int user, int group, int owner, int place, int item) {
  if (conv_uid (user_id) < 0 || !UG_MODE || !valid_type (type)) {
    return -1;
  }

  struct lev_news_item *E = alloc_log_event (LEV_NEWS_ITEM + type, 28, user_id);
  E->user = user;
  E->group = group;
  E->owner = owner;
  E->place = place;
  E->item = item;

  vkprintf (2, "created news item type %08x, user_id=%d\n", E->type, E->user_id);

  return process_news_item (E);
}