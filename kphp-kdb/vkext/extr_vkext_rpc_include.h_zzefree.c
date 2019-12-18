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
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_EFREE (long long) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (void*) ; 
 int /*<<< orphan*/  emalloc ; 

__attribute__((used)) static inline void zzefree (void *p, long long x) {
  ADD_CNT (emalloc);
  START_TIMER (emalloc);
  efree (p);
  END_TIMER (emalloc);
  ADD_EFREE (x);
}