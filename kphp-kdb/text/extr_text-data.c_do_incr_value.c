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
struct value_data {int* data; scalar_t__ zero_mask; } ;
struct lev_incr_field {int local_id; int value; } ;

/* Variables and functions */
 scalar_t__ LEV_TX_INCR_FIELD ; 
 scalar_t__ adjust_message_values (int,int,struct value_data*) ; 
 struct lev_incr_field* alloc_log_event (scalar_t__,int,int) ; 
 struct value_data* alloc_value_data (int) ; 
 scalar_t__ conv_uid (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int read_extra_mask ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int write_extra_mask ; 

int do_incr_value (int user_id, int local_id, int value_id, int incr) {
  if (verbosity > 1) {
    fprintf (stderr, "do_incr_value(%d,%d,%d,%d):\n", user_id, local_id, value_id, incr);
  }
  if (conv_uid (user_id) < 0 || local_id <= 0 || (unsigned) value_id >= 8) {
    return -1;
  }
  if (!((write_extra_mask >> value_id) & 1)) {
    return 0;
  }
  struct lev_incr_field *E = alloc_log_event (LEV_TX_INCR_FIELD + value_id, 16, user_id);
  E->local_id = local_id;
  E->value = incr;

  if (!(read_extra_mask & (1 << value_id))) {
    return 1;
  }

  struct value_data *V = alloc_value_data (1 << value_id);
  V->zero_mask = 0;
  V->data[0] = incr;

  return adjust_message_values (user_id, local_id, V) > 0;
}