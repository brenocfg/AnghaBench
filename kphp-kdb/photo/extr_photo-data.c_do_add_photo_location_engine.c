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
struct lev_photo_add_photo_location_engine {int user_id; int photo_id; int volume_id; int local_id; int extra; unsigned long long secret; } ;

/* Variables and functions */
 scalar_t__ LEV_PHOTO_ADD_PHOTO_LOCATION_ENGINE ; 
 int MY_LOG_EVENT_HANDLER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_photo_location_engine ; 
 struct lev_photo_add_photo_location_engine* alloc_log_event (scalar_t__,int,int) ; 
 int mode ; 

int do_add_photo_location_engine (int uid, int pid, int original, char sz, int rotate, int vid, int local_id, int extra, unsigned long long secret) {
  if (sz < 'a' || sz > 'z' || rotate < 0 || rotate > 3 || original < 0 || original > 1) {
    return 0;
  }

  int size = sizeof (struct lev_photo_add_photo_location_engine);
  struct lev_photo_add_photo_location_engine *E =
    alloc_log_event (LEV_PHOTO_ADD_PHOTO_LOCATION_ENGINE + (mode << 16) + sz + (rotate << 8) + (original << 10), size, uid);

  E->user_id = uid;
  E->photo_id = pid;
  E->volume_id = vid;
  E->local_id = local_id;
  E->extra = extra;
  E->secret = secret;

  return MY_LOG_EVENT_HANDLER (add_photo_location_engine, 1);
}