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
 int /*<<< orphan*/  LEV_CHANGE_FIELDMASK_DELAYED ; 
 int MAX_EXTRA_MASK ; 
 int /*<<< orphan*/  alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  change_extra_mask (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int write_extra_mask ; 

int do_change_mask (int new_mask) {
  if (verbosity > 1) {
    fprintf (stderr, "do_change_mask(%d)\n", new_mask);
  }
  if (new_mask & ~MAX_EXTRA_MASK) {
    return -1;
  }
  if (new_mask == write_extra_mask) {
    return 0;
  }
  alloc_log_event (LEV_CHANGE_FIELDMASK_DELAYED, 8, new_mask);
  change_extra_mask (new_mask);

  return 1;
}