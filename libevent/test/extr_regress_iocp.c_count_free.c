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
 int /*<<< orphan*/  EVTHREAD_FREE_COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVTHREAD_FREE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_cond ; 
 int /*<<< orphan*/  count_lock ; 

__attribute__((used)) static void
count_free(void)
{
	EVTHREAD_FREE_LOCK(count_lock, 0);
	EVTHREAD_FREE_COND(count_cond);
}