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
typedef  int /*<<< orphan*/  user ;
struct lev_hints_user_object_winner {int type; int losers_cnt; int /*<<< orphan*/ * losers; int /*<<< orphan*/  object_type; int /*<<< orphan*/  winner_id; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 int LEV_HINTS_USER_OBJECT_WINNER ; 
 int /*<<< orphan*/ * conv_user_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fading ; 
 int user_object_rating_increment (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int user_object_winner (struct lev_hints_user_object_winner *E) {
  if (!fading) {
    user *cur_user = conv_user_id (E->user_id);
    if (cur_user != NULL) {
      int num = E->type - LEV_HINTS_USER_OBJECT_WINNER;
      int i;
      int res = user_object_rating_increment (cur_user, E->object_type, E->winner_id, E->losers_cnt + 128, num);
      for (i = 0; i < E->losers_cnt; i++) {
        res = res & user_object_rating_increment (cur_user, E->object_type, E->losers[i], -1 + 128, num);
      }
      return res;
    }
  }
  return 0;
}