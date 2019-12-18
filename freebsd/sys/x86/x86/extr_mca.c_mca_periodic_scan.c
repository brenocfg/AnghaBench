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
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  mca_scan_task ; 
 int mca_ticks ; 
 int /*<<< orphan*/  mca_timer ; 
 int /*<<< orphan*/  mca_tq ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mca_periodic_scan(void *arg)
{

	taskqueue_enqueue(mca_tq, &mca_scan_task);
	callout_reset(&mca_timer, mca_ticks * hz, mca_periodic_scan, NULL);
}