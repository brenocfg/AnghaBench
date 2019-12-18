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
 int /*<<< orphan*/  MACHINE_HAS_TOPOLOGY ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_topology_timer () ; 
 int /*<<< orphan*/  topology_poll ; 

void topology_expect_change(void)
{
	if (!MACHINE_HAS_TOPOLOGY)
		return;
	/* This is racy, but it doesn't matter since it is just a heuristic.
	 * Worst case is that we poll in a higher frequency for a bit longer.
	 */
	if (atomic_read(&topology_poll) > 60)
		return;
	atomic_add(60, &topology_poll);
	set_topology_timer();
}