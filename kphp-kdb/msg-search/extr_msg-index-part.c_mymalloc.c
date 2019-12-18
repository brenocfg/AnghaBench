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
 int HEAP_SIZE ; 
 void* Heap ; 
 void* heap_a ; 

void *mymalloc (size_t s) {
  void *res = heap_a;
  if (s > (1L << 25) || heap_a + s > Heap + HEAP_SIZE) return 0;
  heap_a += (s + 3) & -4;
  return res;
}