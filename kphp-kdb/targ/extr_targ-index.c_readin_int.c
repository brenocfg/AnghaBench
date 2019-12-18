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
 int idx_load_next (int) ; 
 scalar_t__ idx_rptr ; 
 scalar_t__ idx_wptr ; 
 scalar_t__ unlikely (int) ; 

int readin_int (void) {
  if (unlikely (idx_rptr + 4 > idx_wptr)) {
    assert (idx_load_next (4) >= 4);
  }
  int x = *((int *) idx_rptr);
  idx_rptr += 4;
  return x;
}