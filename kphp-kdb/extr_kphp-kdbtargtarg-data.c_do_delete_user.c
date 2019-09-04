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
struct lev_delete_user {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_TARG_DELUSER ; 
 struct lev_delete_user* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ conv_user_id (int) ; 
 int delete_user (struct lev_delete_user*) ; 

int do_delete_user (int user_id) {
  if (conv_user_id (user_id) < 0) {
    return 0;
  }
  struct lev_delete_user *E = alloc_log_event (LEV_TARG_DELUSER, 8, user_id);
  return delete_user (E);
}