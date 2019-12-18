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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EVLOCK_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVLOCK_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVTHREAD_COND_WAIT_TIMED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*) ; 
 scalar_t__ GetTickCount () ; 
 int count ; 
 int /*<<< orphan*/  count_cond ; 
 int /*<<< orphan*/  count_lock ; 

__attribute__((used)) static int
count_wait_for(int i, int ms)
{
	struct timeval tv;
	DWORD elapsed;
	int rv = -1;

	EVLOCK_LOCK(count_lock, 0);
	while (ms > 0 && count != i) {
		tv.tv_sec = 0;
		tv.tv_usec = ms * 1000;
		elapsed = GetTickCount();
		EVTHREAD_COND_WAIT_TIMED(count_cond, count_lock, &tv);
		elapsed = GetTickCount() - elapsed;
		ms -= elapsed;
	}
	if (count == i)
		rv = 0;
	EVLOCK_UNLOCK(count_lock, 0);

	return rv;
}