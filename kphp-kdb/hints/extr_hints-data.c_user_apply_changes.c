#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; TYPE_4__* chg_list_global; TYPE_4__* chg_list_cur; } ;
typedef  TYPE_1__ user ;
struct TYPE_7__ {scalar_t__ number; int type; int /*<<< orphan*/  x; struct TYPE_7__* next; } ;

/* Variables and functions */
 int USER_LOADED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  user_do_change (TYPE_1__*,TYPE_4__*) ; 
 scalar_t__ user_has_object (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

void user_apply_changes (user *u) {
  assert (u->flags & USER_LOADED);
  while (u->chg_list_cur->next != NULL || u->chg_list_global->next != NULL) {
    if (u->chg_list_global->next == NULL || (u->chg_list_cur->next != NULL &&
        u->chg_list_cur->next->number < u->chg_list_global->next->number)) {
      u->chg_list_cur = u->chg_list_cur->next;
      user_do_change (u, u->chg_list_cur);
    } else {
      u->chg_list_global = u->chg_list_global->next;
      int type = u->chg_list_global->type;
      if (type >= 256) {
        type -= 256;
      } else if (type < 0) {
        type = -type;
      }
      if (user_has_object (u, type, u->chg_list_global->x)) {
        user_do_change (u, u->chg_list_global);
      }
    }
  }
}