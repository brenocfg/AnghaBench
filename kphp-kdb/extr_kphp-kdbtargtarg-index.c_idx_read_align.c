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
 int /*<<< orphan*/  assert (int) ; 
 int idx_cur_read_pos () ; 
 int idx_load_next (int) ; 
 int idx_rptr ; 

void idx_read_align (int alignment) {
  int to_skip = -idx_cur_read_pos() & (alignment - 1);
  if (to_skip > 0) {
    assert (idx_load_next (to_skip) >= to_skip);
    idx_rptr += to_skip;
  }
}