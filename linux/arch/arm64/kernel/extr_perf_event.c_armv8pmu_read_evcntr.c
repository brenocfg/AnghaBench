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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  armv8pmu_select_counter (int) ; 
 int /*<<< orphan*/  pmxevcntr_el0 ; 
 int /*<<< orphan*/  read_sysreg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 armv8pmu_read_evcntr(int idx)
{
	armv8pmu_select_counter(idx);
	return read_sysreg(pmxevcntr_el0);
}