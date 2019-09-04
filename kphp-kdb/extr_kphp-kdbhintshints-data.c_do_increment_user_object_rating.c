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
struct lev_hints_increment_user_object_rating_char {int user_id; long long object_id; } ;
struct lev_hints_increment_user_object_rating {int user_id; long long object_id; int cnt; } ;

/* Variables and functions */
 scalar_t__ LEV_HINTS_INCREMENT_USER_OBJECT_RATING ; 
 scalar_t__ LEV_HINTS_INCREMENT_USER_OBJECT_RATING_CHAR ; 
 void* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  check_object_id (long long) ; 
 int /*<<< orphan*/  check_rating (int) ; 
 int /*<<< orphan*/  check_rating_num (int) ; 
 int /*<<< orphan*/  check_type (int) ; 
 int /*<<< orphan*/  fading ; 
 int increment_user_object_rating (struct lev_hints_increment_user_object_rating*) ; 
 int increment_user_object_rating_char (struct lev_hints_increment_user_object_rating_char*) ; 

int do_increment_user_object_rating (int user_id, int object_type, long long object_id, int cnt, int num) {
  if (!fading) {
    cnt += 128;
  }
  if (!check_rating (cnt) || !check_type (object_type) || !check_rating_num (num) || !check_object_id (object_id)) {
    return 0;
  }

  if (cnt & -0x100) {
    struct lev_hints_increment_user_object_rating *E =
      alloc_log_event (LEV_HINTS_INCREMENT_USER_OBJECT_RATING + object_type + (num << 8), sizeof (struct lev_hints_increment_user_object_rating), user_id);

    E->user_id = user_id;
    E->object_id = object_id;
    E->cnt = cnt;

    return increment_user_object_rating (E);
  } else {
    struct lev_hints_increment_user_object_rating_char *E =
      alloc_log_event (LEV_HINTS_INCREMENT_USER_OBJECT_RATING_CHAR + object_type + (cnt << 8) + (num << 16), sizeof (struct lev_hints_increment_user_object_rating_char), user_id);

    E->user_id = user_id;
    E->object_id = object_id;

    return increment_user_object_rating_char (E);
  }
}