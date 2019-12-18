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
struct lev_news_comment {int group; int owner; int place; int item; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_MODE ; 
 scalar_t__ LEV_NEWS_COMMENT ; 
 struct lev_news_comment* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  check_obj (int,int,int) ; 
 int process_news_comment (struct lev_news_comment*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int) ; 

int do_process_news_comment (int type, int user, int group, int owner, int place, int item) {
  if (!COMM_MODE || !check_obj (type, owner, place)) {
    return -1;
  }

  struct lev_news_comment *E = alloc_log_event (LEV_NEWS_COMMENT + type, 24, user);
  E->group = group;
  E->owner = owner;
  E->place = place;
  E->item = item;

  vkprintf (2, "created news comment type %08x, place_id=%d\n", E->type, E->place);

  return process_news_comment (E);
}