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
typedef  int /*<<< orphan*/  trp_node ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ ** heap ; 
 int /*<<< orphan*/  heap_fix_down () ; 
 scalar_t__ heap_size ; 

trp_node *heap_get (void) {
  assert (heap_size > 0);

  trp_node *tmp = heap[1];
  heap[1] = heap[heap_size--];
  heap_fix_down();

  return tmp;
}