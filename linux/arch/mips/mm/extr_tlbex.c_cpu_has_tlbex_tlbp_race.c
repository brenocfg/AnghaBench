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
 scalar_t__ cpu_has_htw ; 
 scalar_t__ cpu_has_shared_ftlb_ram ; 

__attribute__((used)) static bool cpu_has_tlbex_tlbp_race(void)
{
	/*
	 * When a Hardware Table Walker is running it can replace TLB entries
	 * at any time, leading to a race between it & the CPU.
	 */
	if (cpu_has_htw)
		return true;

	/*
	 * If the CPU shares FTLB RAM with its siblings then our entry may be
	 * replaced at any time by a sibling performing a write to the FTLB.
	 */
	if (cpu_has_shared_ftlb_ram)
		return true;

	/* In all other cases there ought to be no race condition to handle */
	return false;
}