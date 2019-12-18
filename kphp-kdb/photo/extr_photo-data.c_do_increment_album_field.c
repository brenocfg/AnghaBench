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

/* Variables and functions */
 scalar_t__ ALBUM_TYPE ; 
 int /*<<< orphan*/  LEV_PHOTO_INCREM_ALBUM_FIELD ; 
 int /*<<< orphan*/  check_album_id (int) ; 
 int do_increment_data (int,int,int,int,int /*<<< orphan*/ ) ; 
 int get_field_id (scalar_t__,char*) ; 
 scalar_t__ types ; 

int do_increment_album_field (int uid, int aid, char *field_name, int cnt) {
  if (field_name == NULL) {
    return 0;
  }

  if (!check_album_id (aid)) {
    return 0;
  }

  int field_id = get_field_id (types + ALBUM_TYPE, field_name);
  if (field_id < 0) {
    return 0;
  }

  return do_increment_data (uid, aid, field_id, cnt, LEV_PHOTO_INCREM_ALBUM_FIELD);
}