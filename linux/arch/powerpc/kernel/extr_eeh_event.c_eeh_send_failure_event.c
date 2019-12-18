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
struct eeh_pe {int dummy; } ;

/* Variables and functions */
 int __eeh_send_failure_event (struct eeh_pe*) ; 
 scalar_t__ eeh_debugfs_no_recover ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int eeh_send_failure_event(struct eeh_pe *pe)
{
	/*
	 * If we've manually supressed recovery events via debugfs
	 * then just drop it on the floor.
	 */
	if (eeh_debugfs_no_recover) {
		pr_err("EEH: Event dropped due to no_recover setting\n");
		return 0;
	}

	return __eeh_send_failure_event(pe);
}