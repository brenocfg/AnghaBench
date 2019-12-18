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
typedef  void CRITICAL_SECTION ;

/* Variables and functions */
 scalar_t__ InitializeCriticalSectionAndSpinCount (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIN_COUNT ; 
 int /*<<< orphan*/  mm_free (void*) ; 
 void* mm_malloc (int) ; 

__attribute__((used)) static void *
evthread_win32_lock_create(unsigned locktype)
{
	CRITICAL_SECTION *lock = mm_malloc(sizeof(CRITICAL_SECTION));
	if (!lock)
		return NULL;
	if (InitializeCriticalSectionAndSpinCount(lock, SPIN_COUNT) == 0) {
		mm_free(lock);
		return NULL;
	}
	return lock;
}