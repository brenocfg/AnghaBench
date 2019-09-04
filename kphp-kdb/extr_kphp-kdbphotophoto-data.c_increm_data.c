#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user ;
struct TYPE_5__ {int field_i; TYPE_1__* fields; } ;
typedef  TYPE_2__ type_desc ;
struct lev_photo_increm_data {int type; int /*<<< orphan*/  cnt; int /*<<< orphan*/  data_id; } ;
struct lev_generic {int dummy; } ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ is_const; } ;

/* Variables and functions */
 size_t ALBUM_TYPE ; 
#define  LEV_PHOTO_INCREM_ALBUM_FIELD 129 
#define  LEV_PHOTO_INCREM_PHOTO_FIELD 128 
 size_t PHOTO_TYPE ; 
 int /*<<< orphan*/  assert (int) ; 
 int mode ; 
 scalar_t__ t_int ; 
 TYPE_2__* types ; 
 int /*<<< orphan*/  user_add_change (int /*<<< orphan*/ *,struct lev_generic*,int) ; 
 int user_increm_album_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int user_increm_photo_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_loaded (int /*<<< orphan*/ *) ; 
 scalar_t__ write_only ; 

int increm_data (user *u, struct lev_photo_increm_data *E, int size) {
  if (u == NULL) {
    return 0;
  }

  if (write_only) {
    return 1;
  }

  int field_id = E->type & 255;

  type_desc *t_desc;
  switch (E->type - (mode << 16) - field_id) {
    case LEV_PHOTO_INCREM_PHOTO_FIELD:
      t_desc = &types[PHOTO_TYPE];
      break;
    case LEV_PHOTO_INCREM_ALBUM_FIELD:
      t_desc = &types[ALBUM_TYPE];
      break;
    default:
      assert (0);
      return 0;
  }

  assert (field_id < t_desc->field_i);
  if (t_desc->fields[field_id].is_const) {
    return 0;
  }
  if (t_desc->fields[field_id].type != t_int) {
    return 0;
  }

  if (!user_loaded (u)) {
    user_add_change (u, (struct lev_generic *)E, size);
    return 1;
  }

  switch (E->type - (mode << 16) - field_id) {
    case LEV_PHOTO_INCREM_PHOTO_FIELD:
      return user_increm_photo_field (u, E->data_id, field_id, E->cnt);
    case LEV_PHOTO_INCREM_ALBUM_FIELD:
      return user_increm_album_field (u, E->data_id, field_id, E->cnt);
    default:
      assert (0);
  }
}