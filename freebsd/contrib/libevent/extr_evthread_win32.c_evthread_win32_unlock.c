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
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
evthread_win32_unlock(unsigned mode, void *lock_)
{
	CRITICAL_SECTION *lock = lock_;
	LeaveCriticalSection(lock);
	return 0;
}