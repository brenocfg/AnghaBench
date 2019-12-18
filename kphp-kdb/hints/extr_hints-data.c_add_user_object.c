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
struct lev_hints_add_user_object {int /*<<< orphan*/  object_id; int /*<<< orphan*/  object_type; int /*<<< orphan*/  text; int /*<<< orphan*/  user_id; int /*<<< orphan*/  text_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_text_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * conv_user_id (int /*<<< orphan*/ ) ; 
 int user_add_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

int add_user_object (struct lev_hints_add_user_object *E) {
  if (!check_text_len (E->text_len)) {
    return 0;
  }

  user *cur_user = conv_user_id (E->user_id);
  if (cur_user != NULL) {
#ifdef HINTS
    return user_add_object (cur_user, E->object_type, E->object_id, E->text);
#else
    return user_add_object (cur_user, E->object_type, E->object_id);
#endif
  }

  return 0;
}