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
 void* malloc (size_t) ; 
 size_t memory_used ; 

void *qmalloc (size_t x) {
  memory_used += x;
  void *res = malloc (x);
  assert (x == 0 || res != NULL);
  return res;
}