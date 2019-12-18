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
struct lev_photo_change_photo_location_server {int dummy; } ;
struct lev_photo_add_photo_location {int user_id; int photo_id; int server_id; } ;

/* Variables and functions */
 scalar_t__ LEV_PHOTO_CHANGE_PHOTO_LOCATION_SERVER ; 
 int MY_LOG_EVENT_HANDLER (int /*<<< orphan*/ ,int) ; 
 struct lev_photo_add_photo_location* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  change_photo_location_server ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int mode ; 

int do_change_photo_location_server (int uid, int pid, int original, int server_num, int sid) {
  if (original < 0 || original > 1 || server_num < 0 || server_num > 1) {
    dbg ("change_photo_location_server failed\n");
    return 0;
  }

  int size = sizeof (struct lev_photo_change_photo_location_server);

  struct lev_photo_add_photo_location *E =
    alloc_log_event (LEV_PHOTO_CHANGE_PHOTO_LOCATION_SERVER + (mode << 16) + (original << 1) + server_num, size, uid);

  E->user_id = uid;
  E->photo_id = pid;
  E->server_id = sid;

  return MY_LOG_EVENT_HANDLER (change_photo_location_server, 1);
}