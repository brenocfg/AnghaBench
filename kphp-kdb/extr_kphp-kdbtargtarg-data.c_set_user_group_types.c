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
struct TYPE_3__ {int /*<<< orphan*/  user_group_types; } ;
typedef  TYPE_1__ user_t ;
struct lev_targ_user_group_types {int /*<<< orphan*/  user_group_types; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 TYPE_1__* get_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_user_group_types (struct lev_targ_user_group_types *E) {
  user_t *U = get_user (E->user_id);
  if (!U) {
    return 0;
  }
  memcpy (U->user_group_types, E->user_group_types, 16);
  return 1;
}