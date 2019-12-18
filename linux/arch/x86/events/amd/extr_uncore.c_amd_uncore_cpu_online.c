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
 scalar_t__ amd_uncore_llc ; 
 scalar_t__ amd_uncore_nb ; 
 int /*<<< orphan*/  uncore_online (unsigned int,scalar_t__) ; 

__attribute__((used)) static int amd_uncore_cpu_online(unsigned int cpu)
{
	if (amd_uncore_nb)
		uncore_online(cpu, amd_uncore_nb);

	if (amd_uncore_llc)
		uncore_online(cpu, amd_uncore_llc);

	return 0;
}