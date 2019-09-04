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
struct lev_photo_set_volume {int volume_id; int server_id; } ;

/* Variables and functions */
 scalar_t__ LEV_PHOTO_SET_VOLUME ; 
 struct lev_photo_set_volume* alloc_log_event (scalar_t__,int,int) ; 
 int mode ; 
 int set_volume (struct lev_photo_set_volume*) ; 

int do_set_volume (int vid, int sid) {
  int size = sizeof (struct lev_photo_set_volume);
  struct lev_photo_set_volume *E =
    alloc_log_event (LEV_PHOTO_SET_VOLUME + (mode << 16), size, vid);

  E->volume_id = vid;
  E->server_id = sid;

  return set_volume (E);
}