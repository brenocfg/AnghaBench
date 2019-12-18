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
typedef  int /*<<< orphan*/  CRITICAL_SECTION ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
evthread_win32_lock_free(void *lock_, unsigned locktype)
{
	CRITICAL_SECTION *lock = lock_;
	DeleteCriticalSection(lock);
	mm_free(lock);
}