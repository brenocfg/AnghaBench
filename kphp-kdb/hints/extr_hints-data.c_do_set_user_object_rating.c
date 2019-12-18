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
struct lev_hints_set_user_object_rating {int user_id; long long object_id; float val; } ;

/* Variables and functions */
 scalar_t__ LEV_HINTS_SET_USER_OBJECT_RATING ; 
 struct lev_hints_set_user_object_rating* alloc_log_event (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_object_id (long long) ; 
 int /*<<< orphan*/  check_rating (float) ; 
 int /*<<< orphan*/  check_rating_num (int) ; 
 int /*<<< orphan*/  check_type (int) ; 
 int set_user_object_rating (struct lev_hints_set_user_object_rating*) ; 

int do_set_user_object_rating (int user_id, int object_type, long long object_id, float new_rating, int num) {
  if (!check_type (object_type) || !check_rating_num (num) || !check_object_id (object_id) || !check_rating (new_rating)) {
    return 0;
  }

  struct lev_hints_set_user_object_rating *E =
    alloc_log_event (LEV_HINTS_SET_USER_OBJECT_RATING + (num << 8) + object_type, sizeof (struct lev_hints_set_user_object_rating), 0);

  E->user_id = user_id;
  E->object_id = object_id;
  E->val = new_rating;

  return set_user_object_rating (E);
}