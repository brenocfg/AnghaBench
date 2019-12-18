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
struct cpu_cf_events {int /*<<< orphan*/  alert; } ;

/* Variables and functions */
 unsigned long atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_cf_events ; 
 struct cpu_cf_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

unsigned long kernel_cpumcf_alert(int clear)
{
	struct cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	unsigned long alert;

	alert = atomic64_read(&cpuhw->alert);
	if (clear)
		atomic64_set(&cpuhw->alert, 0);

	return alert;
}