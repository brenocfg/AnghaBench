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
struct lev_news_set_recommend_rate {int action; int type; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/ * recommend_rate_tbl ; 

__attribute__((used)) static int set_recommend_rate (struct lev_news_set_recommend_rate *E) {
  if (E->action < 0 || E->action > 255) {
    return 0;
  }
  recommend_rate_tbl[((E->type & 31) << 8) + E->action] = E->rate;
  return 1;
}