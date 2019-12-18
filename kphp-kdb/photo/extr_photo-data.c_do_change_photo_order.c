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
struct lev_photo_change_photo_order {int user_id; int photo_id; int photo_id_near; } ;

/* Variables and functions */
 scalar_t__ LEV_PHOTO_CHANGE_PHOTO_ORDER ; 
 int MY_LOG_EVENT_HANDLER (int /*<<< orphan*/ ,int) ; 
 struct lev_photo_change_photo_order* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  change_photo_order ; 
 int /*<<< orphan*/  check_photo_id (int) ; 
 int mode ; 

int do_change_photo_order (int uid, int pid, int pid_near, int is_next) {
  if (!check_photo_id (pid) || pid_near < 0 || pid_near == pid) {
    return 0;
  }
  int size = sizeof (struct lev_photo_change_photo_order);
  struct lev_photo_change_photo_order *E =
    alloc_log_event (LEV_PHOTO_CHANGE_PHOTO_ORDER + (mode << 16) + is_next, size, uid);

  E->user_id = uid;
  E->photo_id = pid;
  E->photo_id_near = pid_near;

  return MY_LOG_EVENT_HANDLER (change_photo_order, 1);
}