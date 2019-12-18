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
 int /*<<< orphan*/  ADD_CNT (void* (*) (long long)) ; 
 int /*<<< orphan*/  ADD_MALLOC (long long) ; 
 int /*<<< orphan*/  END_TIMER (void* (*) (long long)) ; 
 int /*<<< orphan*/  START_TIMER (void* (*) (long long)) ; 
 int /*<<< orphan*/  assert (void*) ; 
 void* malloc (long long) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,long long) ; 

__attribute__((used)) static inline void *zzmalloc0 (long long x) {
  ADD_CNT (malloc);
  START_TIMER (malloc);
  void *r = malloc (x);
  assert (r);
  memset (r, 0, x);
  ADD_MALLOC (x);
  END_TIMER (malloc);
  return r;
}