#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  gt_taskqueue; } ;

/* Variables and functions */
 TYPE_1__ free_gtask ; 
 int /*<<< orphan*/  gtaskqueue_drain_all (int /*<<< orphan*/ ) ; 

void
in6m_release_wait(void)
{

	/* Wait for all jobs to complete. */
	gtaskqueue_drain_all(free_gtask.gt_taskqueue);
}