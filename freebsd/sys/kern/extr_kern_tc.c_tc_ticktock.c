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
 scalar_t__ mtx_trylock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_setclock_mtx ; 
 int tc_tick ; 
 int /*<<< orphan*/  tc_windup (int /*<<< orphan*/ *) ; 

void
tc_ticktock(int cnt)
{
	static int count;

	if (mtx_trylock_spin(&tc_setclock_mtx)) {
		count += cnt;
		if (count >= tc_tick) {
			count = 0;
			tc_windup(NULL);
		}
		mtx_unlock_spin(&tc_setclock_mtx);
	}
}