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
struct lev_photo_add_photo_location_engine_old {int type; int /*<<< orphan*/  secret; int /*<<< orphan*/  local_id; int /*<<< orphan*/  volume_id; int /*<<< orphan*/  photo_id; } ;

/* Variables and functions */
 int LEV_PHOTO_ADD_PHOTO_LOCATION_ENGINE_OLD ; 
 int mode ; 
 int user_add_photo_location_engine (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int add_photo_location_engine_old (user *u, struct lev_photo_add_photo_location_engine_old *E, int size) {
  int original_size_rotate = E->type - (mode << 16) - LEV_PHOTO_ADD_PHOTO_LOCATION_ENGINE_OLD;
  return user_add_photo_location_engine (u, E->photo_id, original_size_rotate >> 10, original_size_rotate & 255, (original_size_rotate >> 8) & 3, E->volume_id, E->local_id, 0, E->secret);
}