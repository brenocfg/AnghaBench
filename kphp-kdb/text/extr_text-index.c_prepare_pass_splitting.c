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
 int MAX_PASSES ; 
 int /*<<< orphan*/  assert (int) ; 
 int compute_max_uid (int,int /*<<< orphan*/ ) ; 
 int max_uid ; 
 int* pass_min_uid ; 
 int /*<<< orphan*/  pass_threshold ; 
 int passes ; 
 scalar_t__ temp_binlog_directory ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int prepare_pass_splitting (void) {
  int i, uid = 0;
  assert (passes > 0 && passes <= MAX_PASSES);
  for (i = 0; i < passes; i++) {
    pass_min_uid[i] = uid;
    uid = compute_max_uid (uid, pass_threshold);
  }
  pass_min_uid[i] = uid;
  assert (uid == max_uid + 1);
  if (temp_binlog_directory) {
    if (i <= 2) {
      vkprintf (1, "only %d passes needed, ignoring temporary directory\n", i);
      temp_binlog_directory = 0;
    }
  }
  return i;
}