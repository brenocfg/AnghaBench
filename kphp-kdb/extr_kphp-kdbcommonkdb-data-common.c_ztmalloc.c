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
 void* dyn_top_alloc (long,int /*<<< orphan*/ ) ; 

void *ztmalloc (long size) {
  void *res = dyn_top_alloc (size, PTRSIZE);
  assert (res);
  return res;
}