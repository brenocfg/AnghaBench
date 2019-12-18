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
typedef  int value_t ;
struct lev_new_entry_long {int value; } ;
struct lev_new_entry_ext {int value; int /*<<< orphan*/  extra; } ;
struct lev_new_entry {int dummy; } ;
typedef  int /*<<< orphan*/  object_id_t ;
typedef  int /*<<< orphan*/  list_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_INT (int /*<<< orphan*/ ) ; 
 struct lev_new_entry_ext* LEV_ADJUST_LO (struct lev_new_entry_ext*) ; 
 int LEV_LI_SET_ENTRY ; 
 int LEV_LI_SET_ENTRY_EXT ; 
 int LEV_LI_SET_ENTRY_LONG ; 
 struct lev_new_entry_ext* alloc_log_event (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ conv_list_id (int /*<<< orphan*/ ) ; 
 scalar_t__ entry_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lev_list_object_bytes ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 scalar_t__ metafile_mode ; 
 scalar_t__ prepare_list_metafile (int /*<<< orphan*/ ,int) ; 
 int set_list_entry (struct lev_new_entry_ext*,int,int) ; 
 int /*<<< orphan*/  upcopy_list_object_id (struct lev_new_entry_ext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int do_add_list_entry (list_id_t list_id, object_id_t object_id, int mode, int flags, value_t value, const int *extra) {
  assert (mode >= 0 && mode <= 3);
  if (conv_list_id (list_id) < 0 || (flags & -0x100)) {
    return -1;
  }
  if (metafile_mode && mode != 0 && prepare_list_metafile (list_id, 1) < 0) {
    return -2;
  }
  if (extra && !extra[0] && !extra[1] && !extra[2] && !extra[3]) {
    extra = 0;
  }
  if (extra && mode == 1) {
    extra = 0;
  }
#ifdef VALUES64
  if (extra && value != (int) value) {
    extra = 0;
  }
#endif
  if (mode == 3) {
    mode = 0;
  }

  if (mode == 1 && !entry_exists (list_id, object_id)) {
    return 0;
  }
  if (mode == 2 && entry_exists (list_id, object_id)) {
    return 0;
  }
  struct lev_new_entry_ext *E, *EE;
  int ext;
  if (extra) {
    E = alloc_log_event (LEV_LI_SET_ENTRY_EXT - (mode << 8) + flags, sizeof (struct lev_new_entry_ext) + lev_list_object_bytes, FIRST_INT (list_id));
    upcopy_list_object_id (E, list_id, object_id);
    EE = LEV_ADJUST_LO(E);
    EE->value = value;
    memcpy (EE->extra, extra, 16);
    ext = 0;
#ifdef VALUES64
  } else if (value != (int) value) {
    E = alloc_log_event (LEV_LI_SET_ENTRY_LONG - (mode << 8) + flags, sizeof (struct lev_new_entry_long) + lev_list_object_bytes, FIRST_INT (list_id));
    upcopy_list_object_id (E, list_id, object_id);
    struct lev_new_entry_long *EE = (struct lev_new_entry_long *) LEV_ADJUST_LO(E);
    EE->value = value;
    ext = 2;
#endif
  } else {
    E = alloc_log_event (LEV_LI_SET_ENTRY - (mode << 8) + flags, sizeof (struct lev_new_entry) + lev_list_object_bytes, FIRST_INT (list_id));
    upcopy_list_object_id (E, list_id, object_id);
    EE = LEV_ADJUST_LO(E);
    EE->value = value;
    ext = 1;
  }
  return set_list_entry (E, ext, value);
}