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
struct value_data {int fields_mask; int zero_mask; int* data; } ;
struct lev_set_extra_fields {int local_id; int /*<<< orphan*/  extra; } ;

/* Variables and functions */
 scalar_t__ LEV_TX_SET_EXTRA_FIELDS ; 
 int MAX_EXTRA_MASK ; 
 scalar_t__ adjust_message_values (int,int,struct value_data*) ; 
 struct lev_set_extra_fields* alloc_log_event (scalar_t__,int,int) ; 
 scalar_t__ conv_uid (int) ; 
 struct value_data* convert_value_data (struct value_data*,int,int) ; 
 int extra_mask_intcount (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int write_extra_mask ; 

int do_set_values (int user_id, int local_id, struct value_data *V) {
  if (verbosity > 1) {
    fprintf (stderr, "do_set_values(%d,%d,%d:%d,%d,...):\n", user_id, local_id, V->fields_mask, V->zero_mask, V->fields_mask ? V->data[0] : 0);
  }
  if (V->fields_mask != V->zero_mask || (V->fields_mask & ~MAX_EXTRA_MASK)) {
    return -1;
  }
  if (!(V->fields_mask & write_extra_mask)) {
    return 0;
  }
  if (conv_uid (user_id) < 0 || local_id <= 0) {
    return -1;
  }
  V = convert_value_data (V, 1, write_extra_mask);
  int s = 4 * extra_mask_intcount (V->fields_mask);
  struct lev_set_extra_fields *E = alloc_log_event (LEV_TX_SET_EXTRA_FIELDS + V->fields_mask, 12 + s, user_id);
  E->local_id = local_id;
  memcpy (E->extra, V->data, s);
  return adjust_message_values (user_id, local_id, V) > 0;
}