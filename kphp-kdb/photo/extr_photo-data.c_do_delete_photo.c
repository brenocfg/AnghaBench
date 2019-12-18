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
struct lev_photo_delete_photo {int user_id; int photo_id; } ;

/* Variables and functions */
 scalar_t__ LEV_PHOTO_DELETE_PHOTO ; 
 int MY_LOG_EVENT_HANDLER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lev_photo_delete_photo* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  delete_photo ; 
 int mode ; 

int do_delete_photo (int uid, int pid) {
  int size = sizeof (struct lev_photo_delete_photo);
  struct lev_photo_delete_photo *E =
    alloc_log_event (LEV_PHOTO_DELETE_PHOTO + (mode << 16), size, uid);

  E->user_id = uid;
  E->photo_id = pid;

  return MY_LOG_EVENT_HANDLER (delete_photo, 0);
}