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
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
struct pvclock_vcpu_time_info {int dummy; } ;

/* Variables and functions */
 int PVCLOCK_FLAG_TSC_STABLE ; 
 int /*<<< orphan*/  atomic_cmpset_64 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ atomic_load_acq_64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvclock_last_cycles ; 
 int /*<<< orphan*/  pvclock_read_time_info (struct pvclock_vcpu_time_info*,scalar_t__*,int*) ; 

uint64_t
pvclock_get_timecount(struct pvclock_vcpu_time_info *ti)
{
	uint64_t now, last;
	uint8_t flags;

	pvclock_read_time_info(ti, &now, &flags);

	if (flags & PVCLOCK_FLAG_TSC_STABLE)
		return (now);

	/*
	 * Enforce a monotonically increasing clock time across all VCPUs.
	 * If our time is too old, use the last time and return. Otherwise,
	 * try to update the last time.
	 */
	do {
		last = atomic_load_acq_64(&pvclock_last_cycles);
		if (last > now)
			return (last);
	} while (!atomic_cmpset_64(&pvclock_last_cycles, last, now));

	return (now);
}