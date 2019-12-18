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
struct cpu_hw_events {scalar_t__ n_added; } ;
struct TYPE_2__ {int num_pcrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  calculate_multiple_pcrs (struct cpu_hw_events*) ; 
 int /*<<< orphan*/  calculate_single_pcr (struct cpu_hw_events*) ; 
 int /*<<< orphan*/  read_in_all_counters (struct cpu_hw_events*) ; 
 TYPE_1__* sparc_pmu ; 

__attribute__((used)) static void update_pcrs_for_enable(struct cpu_hw_events *cpuc)
{
	if (cpuc->n_added)
		read_in_all_counters(cpuc);

	if (sparc_pmu->num_pcrs == 1) {
		calculate_single_pcr(cpuc);
	} else {
		calculate_multiple_pcrs(cpuc);
	}
}