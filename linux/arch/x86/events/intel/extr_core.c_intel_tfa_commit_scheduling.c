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
struct cpu_hw_events {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_set_tfa (struct cpu_hw_events*,int) ; 

__attribute__((used)) static void intel_tfa_commit_scheduling(struct cpu_hw_events *cpuc, int idx, int cntr)
{
	/*
	 * We're going to use PMC3, make sure TFA is set before we touch it.
	 */
	if (cntr == 3)
		intel_set_tfa(cpuc, true);
}