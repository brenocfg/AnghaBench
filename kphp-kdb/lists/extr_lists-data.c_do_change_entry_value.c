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
typedef  char value_t ;
struct lev_set_value_long {char value; } ;
struct lev_set_value {char value; } ;
struct lev_generic {int dummy; } ;
struct lev_del_entry {int dummy; } ;
typedef  int /*<<< orphan*/  object_id_t ;
typedef  int /*<<< orphan*/  list_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_INT (int /*<<< orphan*/ ) ; 
 scalar_t__ LEV_ADJUST_LO (struct lev_set_value*) ; 
 scalar_t__ LEV_LI_INCR_VALUE ; 
 scalar_t__ LEV_LI_INCR_VALUE_LONG ; 
 scalar_t__ LEV_LI_INCR_VALUE_TINY ; 
 scalar_t__ LEV_LI_SET_VALUE ; 
 scalar_t__ LEV_LI_SET_VALUE_LONG ; 
 struct lev_set_value* alloc_log_event (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ conv_list_id (int /*<<< orphan*/ ) ; 
 scalar_t__ lev_list_object_bytes ; 
 scalar_t__ metafile_mode ; 
 scalar_t__ prepare_list_metafile (int /*<<< orphan*/ ,int) ; 
 long long set_incr_entry_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int,struct lev_generic*) ; 
 int /*<<< orphan*/  upcopy_list_object_id (struct lev_set_value*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

long long do_change_entry_value (list_id_t list_id, object_id_t object_id, value_t value, int incr) {
  if (conv_list_id (list_id) < 0) {
    return -1LL << 63;
  }
  if (metafile_mode && prepare_list_metafile (list_id, 1) < 0) {
    return -1LL << 63;
  }
  struct lev_set_value *E;
  if (incr && value == (signed char) value) {
    E = alloc_log_event (LEV_LI_INCR_VALUE_TINY + (value & 0xff), sizeof (struct lev_del_entry) + lev_list_object_bytes, FIRST_INT (list_id));
#ifdef VALUES64
  } else if (value != (int) value) {
    E = alloc_log_event (incr ? LEV_LI_INCR_VALUE_LONG : LEV_LI_SET_VALUE_LONG, sizeof (struct lev_set_value_long) + lev_list_object_bytes, FIRST_INT (list_id));
    ((struct lev_set_value_long *) LEV_ADJUST_LO (E))->value = value;
#endif
  } else {
    E = alloc_log_event (incr ? LEV_LI_INCR_VALUE : LEV_LI_SET_VALUE, sizeof (struct lev_set_value) + lev_list_object_bytes, FIRST_INT (list_id));
    ((struct lev_set_value *) LEV_ADJUST_LO (E))->value = value;
  }

  upcopy_list_object_id (E, list_id, object_id);
  return set_incr_entry_value (list_id, object_id, value, incr, (struct lev_generic *)E);
}