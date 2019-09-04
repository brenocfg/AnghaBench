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
struct lev_news_set_recommend_rate {double rate; } ;

/* Variables and functions */
 scalar_t__ LEV_NEWS_SET_RECOMMEND_RATE ; 
 int /*<<< orphan*/  RECOMMEND_MODE ; 
 struct lev_news_set_recommend_rate* alloc_log_event (scalar_t__,int,int) ; 
 int fabs (scalar_t__) ; 
 scalar_t__* recommend_rate_tbl ; 
 int set_recommend_rate (struct lev_news_set_recommend_rate*) ; 
 int /*<<< orphan*/  valid_type (int) ; 

int do_set_recommend_rate (int type, int action, double rate) {
  if (!RECOMMEND_MODE || !valid_type (type)) {
    return -1;
  }
  if (action < 0 || action > 255) {
    return -1;
  }
  if (fabs (recommend_rate_tbl[(type << 8) + action] - rate) < 1e-9) {
    return -1;
  }
  struct lev_news_set_recommend_rate *E = alloc_log_event (LEV_NEWS_SET_RECOMMEND_RATE + type, sizeof (*E), action);
  E->rate = rate;
  return set_recommend_rate (E);
}