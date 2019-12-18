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
struct lev_photo_change_photo_order {int type; int /*<<< orphan*/  photo_id_near; int /*<<< orphan*/  photo_id; } ;

/* Variables and functions */
 int LEV_PHOTO_CHANGE_PHOTO_ORDER ; 
 int mode ; 
 int user_change_photo_order (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int change_photo_order (user *u, struct lev_photo_change_photo_order *E, int size) {
  return user_change_photo_order (u, E->photo_id, E->photo_id_near, E->type - (mode << 16) - LEV_PHOTO_CHANGE_PHOTO_ORDER);
}