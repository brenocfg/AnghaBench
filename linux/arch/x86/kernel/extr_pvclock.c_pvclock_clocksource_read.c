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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
struct pvclock_vcpu_time_info {int flags; } ;

/* Variables and functions */
 int PVCLOCK_GUEST_STOPPED ; 
 int PVCLOCK_TSC_STABLE_BIT ; 
 scalar_t__ __pvclock_read_cycles (struct pvclock_vcpu_time_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic64_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  last_value ; 
 unsigned int pvclock_read_begin (struct pvclock_vcpu_time_info*) ; 
 scalar_t__ pvclock_read_retry (struct pvclock_vcpu_time_info*,unsigned int) ; 
 int /*<<< orphan*/  pvclock_touch_watchdogs () ; 
 int /*<<< orphan*/  rdtsc_ordered () ; 
 scalar_t__ unlikely (int) ; 
 int valid_flags ; 

u64 pvclock_clocksource_read(struct pvclock_vcpu_time_info *src)
{
	unsigned version;
	u64 ret;
	u64 last;
	u8 flags;

	do {
		version = pvclock_read_begin(src);
		ret = __pvclock_read_cycles(src, rdtsc_ordered());
		flags = src->flags;
	} while (pvclock_read_retry(src, version));

	if (unlikely((flags & PVCLOCK_GUEST_STOPPED) != 0)) {
		src->flags &= ~PVCLOCK_GUEST_STOPPED;
		pvclock_touch_watchdogs();
	}

	if ((valid_flags & PVCLOCK_TSC_STABLE_BIT) &&
		(flags & PVCLOCK_TSC_STABLE_BIT))
		return ret;

	/*
	 * Assumption here is that last_value, a global accumulator, always goes
	 * forward. If we are less than that, we should not be much smaller.
	 * We assume there is an error marging we're inside, and then the correction
	 * does not sacrifice accuracy.
	 *
	 * For reads: global may have changed between test and return,
	 * but this means someone else updated poked the clock at a later time.
	 * We just need to make sure we are not seeing a backwards event.
	 *
	 * For updates: last_value = ret is not enough, since two vcpus could be
	 * updating at the same time, and one of them could be slightly behind,
	 * making the assumption that last_value always go forward fail to hold.
	 */
	last = atomic64_read(&last_value);
	do {
		if (ret < last)
			return last;
		last = atomic64_cmpxchg(&last_value, last, ret);
	} while (unlikely(last != ret));

	return ret;
}