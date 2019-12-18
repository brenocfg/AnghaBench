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
struct lev_news_user_comment_hide {int place; int item; int user_id; } ;

/* Variables and functions */
 scalar_t__ LEV_NEWS_HIDEUSERITEM ; 
 int /*<<< orphan*/  NOTIFY_MODE ; 
 struct lev_news_user_comment_hide* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  check_obj (int,int,int) ; 
 int show_hide_user_notify (int,int,int,int,int,int /*<<< orphan*/ ) ; 

int do_delete_user_comment (int user_id, int type, int owner, int place, int item) {
  if (!NOTIFY_MODE || !check_obj (type, owner, place)) {
    return -1;
  }
  struct lev_news_user_comment_hide *E = alloc_log_event (LEV_NEWS_HIDEUSERITEM + type, 20, owner);
  E->place = place;
  E->item = item;
  E->user_id = user_id;

  return show_hide_user_notify (user_id, type, owner, place, item, 0);
}