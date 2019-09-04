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
struct lev_photo_change_album_order {int user_id; int album_id; int album_id_near; } ;

/* Variables and functions */
 scalar_t__ LEV_PHOTO_CHANGE_ALBUM_ORDER ; 
 int MY_LOG_EVENT_HANDLER (int /*<<< orphan*/ ,int) ; 
 struct lev_photo_change_album_order* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  change_album_order ; 
 int mode ; 

int do_change_album_order (int uid, int aid, int aid_near, int is_next) {
  if (aid == 0 || aid_near == aid) {
    return 0;
  }

  int size = sizeof (struct lev_photo_change_album_order);
  struct lev_photo_change_album_order *E =
    alloc_log_event (LEV_PHOTO_CHANGE_ALBUM_ORDER + (mode << 16) + is_next, size, uid);

  E->user_id = uid;
  E->album_id = aid;
  E->album_id_near = aid_near;

  return MY_LOG_EVENT_HANDLER (change_album_order, 1);
}