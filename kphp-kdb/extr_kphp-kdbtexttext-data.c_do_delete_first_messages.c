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
struct lev_del_first_messages {int first_local_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_TX_DEL_FIRST_MESSAGES ; 
 struct lev_del_first_messages* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int delete_first_messages (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int do_delete_first_messages (int user_id, int first_local_id) {
  if (verbosity > 1) {
    fprintf (stderr, "do_delete_first_messages(%d,%d):\n", user_id, first_local_id);
  }
  int res = delete_first_messages (user_id, first_local_id);
  if (verbosity > 1) {
    fprintf (stderr, "delete_first_messages returned %d\n", res);
  }
  if (res <= 0) {
    return res;
  }
  if (res > 0) {
    struct lev_del_first_messages *E = alloc_log_event (LEV_TX_DEL_FIRST_MESSAGES, sizeof (struct lev_del_first_messages), user_id);
    E->first_local_id = res;
  }
  return 1;
}