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
struct lev_photo_add_photo_location {int type; int /*<<< orphan*/  photo; int /*<<< orphan*/  orig_album_id; int /*<<< orphan*/  orig_owner_id; int /*<<< orphan*/  server_id2; int /*<<< orphan*/  server_id; int /*<<< orphan*/  photo_id; } ;

/* Variables and functions */
 int LEV_PHOTO_ADD_PHOTO_LOCATION ; 
 int mode ; 
 int user_add_photo_location (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int add_photo_location (user *u, struct lev_photo_add_photo_location *E, int size) {
  int original = E->type - (mode << 16) - LEV_PHOTO_ADD_PHOTO_LOCATION;
  return user_add_photo_location (u, E->photo_id, original >> 10, E->server_id, E->server_id2, E->orig_owner_id, E->orig_album_id, E->photo);
}