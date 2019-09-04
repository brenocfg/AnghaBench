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
struct lev_hints_del_user_object {int type; int /*<<< orphan*/  object_id; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 int /*<<< orphan*/ * conv_user_id (int /*<<< orphan*/ ) ; 
 int user_del_object (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int del_user_object (struct lev_hints_del_user_object *E) {
  user *cur_user = conv_user_id (E->user_id);

  if (cur_user != NULL) {
    return user_del_object (cur_user, E->type & 0xff, E->object_id, 0);
  }

  return 0;
}