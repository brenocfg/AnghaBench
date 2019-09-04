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
 int MAX_HEAP ; 
 int active_aio_queries ; 
 int /*<<< orphan*/ ** heap ; 
 int /*<<< orphan*/  heap_fix_up (int) ; 
 int heap_size ; 

void heap_add (trp_node *v) {
  if (heap_size + 1 >= MAX_HEAP) {
    active_aio_queries |= (1 << 20);
  }

  if (v != NULL && heap_size + 1 < MAX_HEAP) {
    heap[++heap_size] = v;
    heap_fix_up (heap_size);
  }
}