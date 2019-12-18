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

/* Variables and functions */
 int dl_abs (int) ; 
 int /*<<< orphan*/  h_users ; 
 scalar_t__ import_dump_mode ; 
 int log_split_min ; 
 int log_split_mod ; 
 scalar_t__ set_intp_get (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * users ; 

user *conv_uid_get (int user_id) {
  if (user_id == 0) {
    return NULL;
  }
  if (dl_abs (user_id) % log_split_mod != log_split_min) {
    return NULL;
  }
  if (import_dump_mode) {
    return users;
  }

  user **u = (user **)set_intp_get (&h_users, &user_id);
  if (u == NULL) {
    return NULL;
  }
  return *u;
}