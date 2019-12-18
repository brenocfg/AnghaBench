#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int id; int local_id; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int cur_local_id ; 
 int /*<<< orphan*/  h_users ; 
 scalar_t__ hset_intp_add (int /*<<< orphan*/ *,int*) ; 
 int log_split_min ; 
 int log_split_mod ; 
 int user_cnt ; 
 TYPE_1__* users ; 

user *conv_uid (int user_id) {
  if (user_id <= 0) {
    return NULL;
  }
  if (user_id % log_split_mod != log_split_min) {
    return NULL;
  }
  user **u = (user **)hset_intp_add (&h_users, &user_id);
  if (*u == (user *)&user_id) {
    assert (cur_local_id + 1 < user_cnt);

    *u = &users[++cur_local_id];
    (*u)->id = user_id;
    (*u)->local_id = cur_local_id;
  }
  return *u;
}