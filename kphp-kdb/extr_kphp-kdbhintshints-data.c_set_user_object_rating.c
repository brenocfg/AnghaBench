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
struct lev_hints_set_user_object_rating {int type; int /*<<< orphan*/  val; int /*<<< orphan*/  object_id; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 int LEV_HINTS_SET_USER_OBJECT_RATING ; 
 int /*<<< orphan*/ * conv_user_id (int /*<<< orphan*/ ) ; 
 int user_set_object_rating (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int set_user_object_rating (struct lev_hints_set_user_object_rating *E) {
  user *cur_user = conv_user_id (E->user_id);

  if (cur_user != NULL) {
    int num = (E->type - LEV_HINTS_SET_USER_OBJECT_RATING) >> 8;

    return user_set_object_rating (cur_user, E->type & 0xff, E->object_id, E->val, num);
  }

  return 0;
}