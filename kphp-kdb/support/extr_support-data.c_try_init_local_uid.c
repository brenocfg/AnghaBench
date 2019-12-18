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

/* Variables and functions */
 int /*<<< orphan*/  SUPPORT_SCHEMA_V1 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  init_support_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_schema ; 
 int log_split_max ; 
 int log_split_min ; 
 int log_split_mod ; 

void try_init_local_uid (void) {
  static int was = 0;
  static int old_log_split_min, old_log_split_max, old_log_split_mod;

  if (was) {
//    fprintf (stderr, "%d vs %d | %d vs %d | %d vs %d\n", old_log_split_min, log_split_min, old_log_split_max, log_split_max, old_log_split_mod, log_split_mod);
    assert (old_log_split_min == log_split_min && old_log_split_max == log_split_max && old_log_split_mod == log_split_mod);
    return;
  } else {
    was = 1;
    old_log_split_min = log_split_min;
    old_log_split_max = log_split_max;
    old_log_split_mod = log_split_mod;
  }

  log_schema = SUPPORT_SCHEMA_V1;
  init_support_data (log_schema);
}