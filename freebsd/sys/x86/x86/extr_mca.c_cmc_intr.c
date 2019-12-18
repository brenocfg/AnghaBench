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
 int /*<<< orphan*/  CMCI ; 
 int /*<<< orphan*/  mca_process_records (int /*<<< orphan*/ ) ; 
 scalar_t__ mca_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
cmc_intr(void)
{

	/*
	 * Serialize MCA bank scanning to prevent collisions from
	 * sibling threads.
	 *
	 * If we found anything, log them to the console.
	 */
	if (mca_scan(CMCI, NULL) != 0)
		mca_process_records(CMCI);
}