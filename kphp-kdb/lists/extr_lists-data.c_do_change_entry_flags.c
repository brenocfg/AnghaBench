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
struct lev_set_flags_long {int flags; int and_mask; int xor_mask; } ;
struct lev_set_flags {int flags; int and_mask; int xor_mask; } ;
struct lev_change_flags_long {int flags; int and_mask; int xor_mask; } ;
typedef  int /*<<< orphan*/  object_id_t ;
typedef  int /*<<< orphan*/  list_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_INT (int /*<<< orphan*/ ) ; 
 struct lev_set_flags_long* LEV_ADJUST_LO (struct lev_set_flags_long*) ; 
 scalar_t__ LEV_LI_CHANGE_FLAGS_LONG ; 
 scalar_t__ LEV_LI_DECR_FLAGS ; 
 scalar_t__ LEV_LI_INCR_FLAGS ; 
 scalar_t__ LEV_LI_SET_FLAGS ; 
 scalar_t__ LEV_LI_SET_FLAGS_LONG ; 
 struct lev_set_flags_long* alloc_log_event (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ conv_list_id (int /*<<< orphan*/ ) ; 
 scalar_t__ lev_list_object_bytes ; 
 scalar_t__ metafile_mode ; 
 scalar_t__ prepare_list_metafile (int /*<<< orphan*/ ,int) ; 
 int set_entry_flags (struct lev_set_flags_long*) ; 
 int /*<<< orphan*/  upcopy_list_object_id (struct lev_set_flags_long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int do_change_entry_flags (list_id_t list_id, object_id_t object_id, int set_flags, int clear_flags) {
  int res = 0;
  if (conv_list_id (list_id) < 0) {
    return -1;
  }
  if (metafile_mode && prepare_list_metafile (list_id, 1) < 0) {
    return -2;
  }
  if ((clear_flags | set_flags) == -1 && !(set_flags & -0x100)) {
    struct lev_set_flags *E = alloc_log_event (LEV_LI_SET_FLAGS + set_flags, sizeof (struct lev_set_flags) + lev_list_object_bytes, FIRST_INT(list_id));
    upcopy_list_object_id (E, list_id, object_id);
    return set_entry_flags (E);
  }
  if ((set_flags & -0x100) || (clear_flags & -0x100)) {
    if ((clear_flags | set_flags) == -1) {
      struct lev_set_flags_long *E = alloc_log_event (LEV_LI_SET_FLAGS_LONG, sizeof (struct lev_set_flags_long) + lev_list_object_bytes, FIRST_INT(list_id));
      upcopy_list_object_id (E, list_id, object_id);
      ((struct lev_set_flags_long *) LEV_ADJUST_LO (E))->flags = set_flags;
      return set_entry_flags ((struct lev_set_flags *) E);
    } else {
      struct lev_change_flags_long *E = alloc_log_event (LEV_LI_CHANGE_FLAGS_LONG, sizeof (struct lev_change_flags_long) + lev_list_object_bytes, FIRST_INT(list_id));
      upcopy_list_object_id (E, list_id, object_id);
      struct lev_change_flags_long *EE = LEV_ADJUST_LO (E);
      EE->and_mask = ~(clear_flags | set_flags);
      EE->xor_mask = set_flags;
      return set_entry_flags ((struct lev_set_flags *) E);
    }
  }
  if (clear_flags &= ~set_flags) {
    struct lev_set_flags *E = alloc_log_event (LEV_LI_DECR_FLAGS + clear_flags, sizeof (struct lev_set_flags) + lev_list_object_bytes, FIRST_INT(list_id));
    upcopy_list_object_id (E, list_id, object_id);
    res = set_entry_flags (E);
  }
  if (set_flags) {
    struct lev_set_flags *E = alloc_log_event (LEV_LI_INCR_FLAGS + set_flags, sizeof (struct lev_set_flags) + lev_list_object_bytes, FIRST_INT(list_id));
    upcopy_list_object_id (E, list_id, object_id);
    res = set_entry_flags (E);
  }
  return res;
}