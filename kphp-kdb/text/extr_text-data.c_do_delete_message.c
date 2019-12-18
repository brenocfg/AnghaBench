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
struct lev_del_message {int local_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_TX_DEL_MESSAGE ; 
 int adjust_message (int,int,int,int,int /*<<< orphan*/ ) ; 
 struct lev_del_message* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 scalar_t__ write_all_events ; 

int do_delete_message (int user_id, int local_id) {
  if (verbosity > 1) {
    fprintf (stderr, "do_delete_message(%d,%d):\n", user_id, local_id);
  }
  int res = adjust_message (user_id, local_id, -1, -1, 0);
  if (verbosity > 1) {
    fprintf (stderr, "adjust_message returned %d\n", res);
  }
  if (res < 0) {
    return res;
  }
  if ((res & 1) || write_all_events) {
    struct lev_del_message *E = alloc_log_event (LEV_TX_DEL_MESSAGE, sizeof (struct lev_del_message), user_id);
    E->local_id = local_id;
  }
  return res & 1;
}