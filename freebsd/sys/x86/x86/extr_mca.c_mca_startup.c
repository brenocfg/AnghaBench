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
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hz ; 
 scalar_t__ mca_banks ; 
 int /*<<< orphan*/  mca_periodic_scan ; 
 int mca_ticks ; 
 int /*<<< orphan*/  mca_timer ; 

__attribute__((used)) static void
mca_startup(void *dummy)
{

	if (mca_banks <= 0)
		return;

	callout_reset(&mca_timer, mca_ticks * hz, mca_periodic_scan, NULL);
}