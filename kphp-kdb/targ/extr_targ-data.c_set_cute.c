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
struct TYPE_3__ {int /*<<< orphan*/  cute; } ;
typedef  TYPE_1__ user_t ;
struct lev_cute {scalar_t__ type; int /*<<< orphan*/  cute; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 scalar_t__ LEV_TARG_CUTE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* get_user (int /*<<< orphan*/ ) ; 

void set_cute (struct lev_cute *E) {
  assert (E->type == LEV_TARG_CUTE);
  user_t *U = get_user (E->user_id);
  if (U) {
    U->cute = E->cute;
  }
}