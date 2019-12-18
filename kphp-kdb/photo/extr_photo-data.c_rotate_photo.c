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
struct lev_photo_rotate_photo {int type; int /*<<< orphan*/  photo_id; } ;

/* Variables and functions */
 int LEV_PHOTO_ROTATE_PHOTO ; 
 int mode ; 
 int user_rotate_photo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int rotate_photo (user *u, struct lev_photo_rotate_photo *E, int size) {
  return user_rotate_photo (u, E->photo_id, E->type - (mode << 16) - LEV_PHOTO_ROTATE_PHOTO);
}