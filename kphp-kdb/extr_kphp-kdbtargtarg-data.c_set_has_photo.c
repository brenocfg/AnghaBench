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
struct TYPE_3__ {int has_photo; int /*<<< orphan*/  uid; } ;
typedef  TYPE_1__ user_t ;
struct lev_generic {int type; int /*<<< orphan*/  a; } ;

/* Variables and functions */
 TYPE_1__* get_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_has_photo ; 
 int /*<<< orphan*/  q_pays_money ; 
 int /*<<< orphan*/  q_uses_apps ; 
 int /*<<< orphan*/  user_change_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int set_has_photo (struct lev_generic *E) {
  user_t *U = get_user (E->a);
  if (!U) { return 0; }
  int has_photo = E->type & 0xff;
  user_change_field (U->uid, q_has_photo, (U->has_photo & 0x81) == 1, (has_photo & 0x81) == 1);
  user_change_field (U->uid, q_uses_apps, (U->has_photo & 0x82) == 2, (has_photo & 0x82) == 2);
  user_change_field (U->uid, q_pays_money, (U->has_photo & 0x84) == 4, (has_photo & 0x84) == 4);
  U->has_photo = has_photo;
  return 1;
}