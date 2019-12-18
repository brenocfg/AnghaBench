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
struct lev_generic {int dummy; } ;
struct lev_del_friend {int friend_id; } ;
struct lev_add_friend {int friend_id; int cat; } ;

/* Variables and functions */
 scalar_t__ LEV_FR_ADDTO_CAT ; 
 scalar_t__ LEV_FR_ADD_FRIEND ; 
 scalar_t__ LEV_FR_EDIT_FRIEND ; 
 scalar_t__ LEV_FR_EDIT_FRIEND_AND ; 
 scalar_t__ LEV_FR_EDIT_FRIEND_OR ; 
 scalar_t__ LEV_FR_REMFROM_CAT ; 
 void* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int b_log2 (int) ; 
 int change_friend_logevent (struct lev_generic*) ; 
 scalar_t__ conv_uid (int) ; 
 int get_friend_cat (int,int) ; 
 int /*<<< orphan*/  get_user (int) ; 

int do_add_friend (int user_id, int friend_id, int cat_xor, int cat_and, int force) {
  if (conv_uid (user_id) < 0 || friend_id <= 0 || cat_xor < 0) {
    return -1;
  }
  if ((force && cat_and) || (cat_xor & cat_and)) {
    return -1;
  }
  if (force) {
    struct lev_add_friend *E = alloc_log_event (LEV_FR_ADD_FRIEND, 16, user_id);
    E->friend_id = friend_id;
    E->cat = cat_xor | 1;
    return change_friend_logevent ((struct lev_generic *) E);
  }

  if ((cat_and & 0x7ffffffe) == 0x7ffffffe && !cat_xor) {
    return get_friend_cat (user_id, friend_id);
  }

  if (!get_user (user_id)) {
    return -1;
  }

  int i, m, res = -1;
  m = ~(cat_and | cat_xor) & 0x7ffffffe;
  if (m) {
    if (!(m & (m - 1))) {
      i = b_log2 (m);
      struct lev_del_friend *E = alloc_log_event (LEV_FR_REMFROM_CAT + i, 12, user_id);
      E->friend_id = friend_id;
      res = change_friend_logevent ((struct lev_generic *) E);
    } else if (cat_and & 0x7ffffffe) {
      struct lev_add_friend *E = alloc_log_event (LEV_FR_EDIT_FRIEND_AND, 16, user_id);
      E->friend_id = friend_id;
      E->cat = cat_and | 1;
      res = change_friend_logevent ((struct lev_generic *) E);
    }
  }

  cat_xor &= 0x7ffffffe;
  if (!(cat_and & 0x7ffffffe)) {
    struct lev_add_friend *E = alloc_log_event (LEV_FR_EDIT_FRIEND, 16, user_id);
    E->friend_id = friend_id;
    E->cat = cat_xor | 1;
    res = change_friend_logevent ((struct lev_generic *) E);
  } else if (cat_xor) {
    if (!(cat_xor & (cat_xor - 1))) {
      i = b_log2 (cat_xor);
      struct lev_del_friend *E = alloc_log_event (LEV_FR_ADDTO_CAT + i, 12, user_id);
      E->friend_id = friend_id;
      res = change_friend_logevent ((struct lev_generic *) E);
    } else {
      struct lev_add_friend *E = alloc_log_event (LEV_FR_EDIT_FRIEND_OR, 16, user_id);
      E->friend_id = friend_id;
      E->cat = cat_xor;
      res = change_friend_logevent ((struct lev_generic *) E);
    }
  }

  assert (res != -1);

  return res;
}