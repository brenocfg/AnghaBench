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
typedef  int /*<<< orphan*/  vmci_work_fn ;

/* Variables and functions */
 int vmci_schedule_delayed_work_fn (int /*<<< orphan*/ *,void*) ; 

int
vmci_schedule_delayed_work(vmci_work_fn *work_fn, void *data)
{

	return (vmci_schedule_delayed_work_fn(work_fn, data));
}