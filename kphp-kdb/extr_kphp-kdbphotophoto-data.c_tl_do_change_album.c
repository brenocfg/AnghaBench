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
struct tl_change_album {scalar_t__ changes_len; int /*<<< orphan*/  album_id; int /*<<< orphan*/  user_id; int /*<<< orphan*/  changes; int /*<<< orphan*/  mask; } ;
struct tl_act_extra {scalar_t__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALBUM_TYPE ; 
 int /*<<< orphan*/  LEV_PHOTO_CHANGE_ALBUM ; 
 scalar_t__ MAX_EVENT_SIZE ; 
 int /*<<< orphan*/  TL_BOOL_FALSE ; 
 int /*<<< orphan*/  TL_BOOL_TRUE ; 
 int /*<<< orphan*/  TL_ERROR_BAD_VALUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ check_album_id (int /*<<< orphan*/ ) ; 
 int do_change_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ field_changes_n ; 
 scalar_t__ location_changes_n ; 
 scalar_t__ rpc_get_fields (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 

int tl_do_change_album (struct tl_act_extra *extra) {
  struct tl_change_album *e = (struct tl_change_album *)extra->extra;

  assert (check_album_id (e->album_id) && 0 < e->changes_len && e->changes_len < MAX_EVENT_SIZE);

  if (rpc_get_fields (ALBUM_TYPE, e->mask, e->changes, e->changes_len) < 0) {
    tl_fetch_set_error_format (TL_ERROR_BAD_VALUE, "Can't parse changes");
    return -1;
  }

  int res = 1;
  if (field_changes_n != 0) {
    res &= do_change_data (e->user_id, e->album_id, LEV_PHOTO_CHANGE_ALBUM);
  }
  assert (location_changes_n == 0);

  tl_store_int (res ? TL_BOOL_TRUE : TL_BOOL_FALSE);
  return 0;
}