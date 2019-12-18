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
struct lev_photo_create_photo {int user_id; int album_id; } ;

/* Variables and functions */
 scalar_t__ LEV_PHOTO_CREATE_PHOTO ; 
 int MAX_PHOTOS ; 
 int MY_LOG_EVENT_HANDLER (int /*<<< orphan*/ ,int) ; 
 struct lev_photo_create_photo* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  create_photo ; 
 int mode ; 

int do_create_photo (int uid, int aid, int cnt) {
  if (cnt <= 0 || cnt > MAX_PHOTOS) {
    return 0;
  }

  int size = sizeof (struct lev_photo_create_photo);
  struct lev_photo_create_photo *E =
    alloc_log_event (LEV_PHOTO_CREATE_PHOTO + (mode << 16) + cnt, size, uid);

  E->user_id = uid;
  E->album_id = aid;

  return MY_LOG_EVENT_HANDLER (create_photo, 1);
}