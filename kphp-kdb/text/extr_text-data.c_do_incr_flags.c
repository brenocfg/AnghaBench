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
struct lev_set_flags_long {int local_id; int flags; } ;
struct lev_set_flags {int local_id; } ;

/* Variables and functions */
 scalar_t__ LEV_TX_INCR_MESSAGE_FLAGS ; 
 scalar_t__ LEV_TX_INCR_MESSAGE_FLAGS_LONG ; 
 int adjust_message (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int get_message_flags (int,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 scalar_t__ write_all_events ; 

int do_incr_flags (int user_id, int local_id, int flags) {
  if (verbosity > 1) {
    fprintf (stderr, "do_incr_flags(%d,%d,%d):\n", user_id, local_id, flags);
  }
  if (flags & -0x10000) {
    return -1;
  }
  int res = adjust_message (user_id, local_id, 0, flags, 0);
  if (verbosity > 1) {
    fprintf (stderr, "adjust_message returned %d\n", res);
  }
  if (res < 0) {
    return res;
  }
  if ((res & 1) || write_all_events) {
    if (flags & -0x100) {
      struct lev_set_flags_long *E = alloc_log_event (LEV_TX_INCR_MESSAGE_FLAGS_LONG, sizeof (struct lev_set_flags_long), user_id);
      E->local_id = local_id;
      E->flags = flags;
    } else {
      struct lev_set_flags *E = alloc_log_event (LEV_TX_INCR_MESSAGE_FLAGS + flags, sizeof (struct lev_set_flags), user_id);
      E->local_id = local_id;
    }
  }
  return get_message_flags (user_id, local_id, -1);
}