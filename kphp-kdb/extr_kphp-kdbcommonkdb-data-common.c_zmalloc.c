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
 int /*<<< orphan*/  PTRSIZE ; 
 int /*<<< orphan*/  assert (void*) ; 
 void* dyn_alloc (long,int /*<<< orphan*/ ) ; 

void *zmalloc (long size) {
  void *res = dyn_alloc (size, PTRSIZE);
  assert (res);
  return res;
}