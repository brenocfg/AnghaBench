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
 int* buffer_stack ; 
 size_t buffer_stack_size ; 
 scalar_t__ free_LRU () ; 

int get_new_entry (void) {
  if (buffer_stack_size == 0) {
    assert (free_LRU() == 0);
  }

  return buffer_stack[--buffer_stack_size];
}