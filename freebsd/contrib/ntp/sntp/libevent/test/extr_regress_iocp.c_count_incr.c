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
 int /*<<< orphan*/  EVLOCK_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVLOCK_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVTHREAD_COND_BROADCAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count ; 
 int /*<<< orphan*/  count_cond ; 
 int /*<<< orphan*/  count_lock ; 

__attribute__((used)) static void
count_incr(void)
{
	EVLOCK_LOCK(count_lock, 0);
	count++;
	EVTHREAD_COND_BROADCAST(count_cond);
	EVLOCK_UNLOCK(count_lock, 0);
}