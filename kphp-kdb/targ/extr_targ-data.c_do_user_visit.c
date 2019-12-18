#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int last_visited; } ;
typedef  TYPE_1__ user_t ;
struct lev_online_lite {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_TARG_ONLINE_LITE ; 
 int MAX_ONLINE_DELAY ; 
 struct lev_online_lite* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 TYPE_1__* get_user (int) ; 
 int now ; 
 int /*<<< orphan*/  process_user_online_lite (struct lev_online_lite*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int do_user_visit (int user_id, const char *addr, int len) {
  user_t *U = get_user (user_id);

  if (!U) {
    if (verbosity > 0) {
      fprintf (stderr, "error: unknown user %d, visit neglected\n", user_id);
    }
    return 0;
  }

  if (verbosity > 1) {
    fprintf (stderr, "setting last_visited for user %d to %d\n", user_id, now);
  }

  if (now - U->last_visited >= MAX_ONLINE_DELAY) {
    struct lev_online_lite *E = alloc_log_event (LEV_TARG_ONLINE_LITE, 8, user_id);
    process_user_online_lite (E);
  }

  return 1;
}