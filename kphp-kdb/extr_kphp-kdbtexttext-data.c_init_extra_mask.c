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
 int MAX_EXTRA_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int extra_ints ; 
 int extra_mask_intcount (int) ; 
 int /*<<< orphan*/  incore_messages ; 
 int index_extra_mask ; 
 int read_extra_mask ; 
 int text_shift ; 
 int /*<<< orphan*/  tree_nodes ; 
 int write_extra_mask ; 

__attribute__((used)) static void init_extra_mask (int value) {
  assert (!index_extra_mask && !tree_nodes && !incore_messages);
  index_extra_mask = read_extra_mask = write_extra_mask = value;
  assert (!(index_extra_mask & ~MAX_EXTRA_MASK));
  extra_ints = extra_mask_intcount (index_extra_mask);
  text_shift = extra_ints * 4;
}