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
 int /*<<< orphan*/  ADD_EMALLOC (long long) ; 
 int /*<<< orphan*/  END_TIMER (void* (*) (long long)) ; 
 int /*<<< orphan*/  START_TIMER (void* (*) (long long)) ; 
 int /*<<< orphan*/  assert (void*) ; 
 void* emalloc (long long) ; 

__attribute__((used)) static inline void *zzemalloc (long long x) {
  ADD_CNT (emalloc);
  START_TIMER (emalloc);
  void *r = emalloc (x);
  END_TIMER (emalloc);
  assert (r);
  ADD_EMALLOC (x);
  return r;
}