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
struct lev_photo_restore_photo_location {int user_id; int photo_id; } ;

/* Variables and functions */
 scalar_t__ LEV_PHOTO_RESTORE_PHOTO_LOCATION ; 
 int MY_LOG_EVENT_HANDLER (int /*<<< orphan*/ ,int) ; 
 struct lev_photo_restore_photo_location* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  check_photo_id (int) ; 
 int mode ; 
 int /*<<< orphan*/  restore_photo_location ; 

int do_restore_photo_location (int uid, int pid) {
  if (!check_photo_id (pid)) {
    return 0;
  }

  int size = sizeof (struct lev_photo_restore_photo_location);
  struct lev_photo_restore_photo_location *E =
    alloc_log_event (LEV_PHOTO_RESTORE_PHOTO_LOCATION + (mode << 16), size, uid);

  E->user_id = uid;
  E->photo_id = pid;

  return MY_LOG_EVENT_HANDLER (restore_photo_location, 1);
}