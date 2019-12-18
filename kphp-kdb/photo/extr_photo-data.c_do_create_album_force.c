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
struct lev_photo_create_album_force {int user_id; int album_id; } ;

/* Variables and functions */
 scalar_t__ LEV_PHOTO_CREATE_ALBUM_FORCE ; 
 int MY_LOG_EVENT_HANDLER (int /*<<< orphan*/ ,int) ; 
 struct lev_photo_create_album_force* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  check_album_id (int) ; 
 int /*<<< orphan*/  create_album_force ; 
 int mode ; 

int do_create_album_force (int uid, int aid) {
  if (!check_album_id (aid)) {
    return 0;
  }
  int size = sizeof (struct lev_photo_create_album_force);
  struct lev_photo_create_album_force *E =
    alloc_log_event (LEV_PHOTO_CREATE_ALBUM_FORCE + (mode << 16), size, uid);

  E->user_id = uid;
  E->album_id = aid;

  return MY_LOG_EVENT_HANDLER (create_album_force, 1);
}