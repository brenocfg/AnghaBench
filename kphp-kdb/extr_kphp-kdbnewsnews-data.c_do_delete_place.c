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
struct lev_news_place_delete {int place; } ;

/* Variables and functions */
 scalar_t__ LEV_NEWS_PLACEDEL ; 
 struct lev_news_place_delete* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  check_obj (int,int,int) ; 
 int delete_place (int,int,int) ; 

int do_delete_place (int type, int owner, int place) {
  if (!check_obj (type, owner, place)) {
    return -1;
  }

  struct lev_news_place_delete *E = alloc_log_event (LEV_NEWS_PLACEDEL + type, 12, owner);
  E->place = place;

  return delete_place (type, owner, place);
}