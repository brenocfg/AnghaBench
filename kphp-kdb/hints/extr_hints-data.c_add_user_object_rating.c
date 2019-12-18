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
struct lev_hints_add_user_object_rating {int type; int text_len; int /*<<< orphan*/  object_id; int /*<<< orphan*/  object_type; int /*<<< orphan*/  text; int /*<<< orphan*/  user_id; } ;
typedef  int /*<<< orphan*/  rating ;

/* Variables and functions */
 int LEV_HINTS_ADD_USER_OBJECT_RATING ; 
 int /*<<< orphan*/  check_text_len (int) ; 
 int /*<<< orphan*/ * conv_user_id (int /*<<< orphan*/ ) ; 
 int rating_num ; 
 int user_add_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int user_set_object_rating (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int add_user_object_rating (struct lev_hints_add_user_object_rating *E) {
  int cur_rating_num = E->type - LEV_HINTS_ADD_USER_OBJECT_RATING;
  int text_len = E->text_len - sizeof (float) * cur_rating_num;

  if (!check_text_len (text_len)) {
    return 0;
  }

  user *cur_user = conv_user_id (E->user_id);
  if (cur_user != NULL) {
    int res, num;
    float *ratings;
#ifdef HINTS
    res = user_add_object (cur_user, E->object_type, E->object_id, E->text);
#else
    res = user_add_object (cur_user, E->object_type, E->object_id);
#endif
    ratings = (float *)(E->text + 1 + text_len);

    for (num = 0; num < rating_num && num < cur_rating_num; num++) {
      res &= user_set_object_rating (cur_user, E->object_type, E->object_id, (rating)ratings[num], num);
    }

    return res;
  }

  return 0;
}