#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ user ;
struct lev_hints_set_user_info {int type; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_USER_INFO (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* conv_user_id (int /*<<< orphan*/ ) ; 

int set_user_info (struct lev_hints_set_user_info *E) {
  user *cur_user = conv_user_id (E->user_id);

  if (cur_user == NULL) {
    return 0;
  }

  cur_user->flags = SET_USER_INFO(cur_user->flags, (E->type & 0xff) - 2);

  return 1;
}