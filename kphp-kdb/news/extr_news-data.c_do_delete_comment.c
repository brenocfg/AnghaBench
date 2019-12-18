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
struct lev_news_comment_hide {int place; int item; } ;

/* Variables and functions */
 scalar_t__ COMM_MODE ; 
 scalar_t__ LEV_NEWS_HIDEITEM ; 
 struct lev_news_comment_hide* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  check_obj (int,int,int) ; 
 int show_hide_comment (int,int,int,int,int /*<<< orphan*/ ) ; 
 int show_hide_notify (int,int,int,int,int /*<<< orphan*/ ) ; 

int do_delete_comment (int type, int owner, int place, int item) {
  if (!check_obj (type, owner, place)) {
    return -1;
  }
  struct lev_news_comment_hide *E = alloc_log_event (LEV_NEWS_HIDEITEM + type, 16, owner);
  E->place = place;
  E->item = item;

  if (COMM_MODE) {
    return show_hide_comment (type, owner, place, item, 0);
  } else {
    return show_hide_notify (type, owner, place, item, 0);
  }
}