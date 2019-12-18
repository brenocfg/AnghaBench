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
struct lev_news_recommend {int owner; int place; int action; int item; int item_creation_time; } ;

/* Variables and functions */
 scalar_t__ LEV_NEWS_RECOMMEND ; 
 int /*<<< orphan*/  RECOMMEND_MODE ; 
 struct lev_news_recommend* alloc_log_event (scalar_t__,int,int) ; 
 scalar_t__ conv_uid (int) ; 
 int process_news_recommend (struct lev_news_recommend*) ; 
 int /*<<< orphan*/ * recommend_item_f (int,int,int,int,int) ; 
 int /*<<< orphan*/  valid_type (int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int,int,int,int) ; 

int do_process_news_recommend (int user_id, int type, int owner, int place, int action, int item, int item_creation_time) {
  if (conv_uid (user_id) < 0 || !RECOMMEND_MODE || !valid_type (type)) {
    return -1;
  }
  if (recommend_item_f (user_id, type, owner, place, action) != NULL) {
    vkprintf (4, "recommend_item_f (%d, %d, %d, %d, %d) returns not NULL.\n", user_id, type, owner, place, action);
    return 0;
  }

  struct lev_news_recommend *E = alloc_log_event (LEV_NEWS_RECOMMEND + type, sizeof (*E), user_id);
  E->owner = owner;
  E->place = place;
  E->action = action;
  E->item = item;
  //E->rate = rate;
  E->item_creation_time = item_creation_time;

  return process_news_recommend (E);
}