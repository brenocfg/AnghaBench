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
typedef  int uint64_t ;
struct pvclock_vcpu_time_info {unsigned long long tsc_to_system_mul; int tsc_shift; } ;

/* Variables and functions */

uint64_t
pvclock_tsc_freq(struct pvclock_vcpu_time_info *ti)
{
	uint64_t freq;

	freq = (1000000000ULL << 32) / ti->tsc_to_system_mul;

	if (ti->tsc_shift < 0)
		freq <<= -ti->tsc_shift;
	else
		freq >>= ti->tsc_shift;

	return (freq);
}