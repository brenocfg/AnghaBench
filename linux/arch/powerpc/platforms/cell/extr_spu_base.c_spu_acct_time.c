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
struct TYPE_2__ {unsigned long long* times; int util_state; scalar_t__ tstamp; } ;
struct spu {TYPE_1__ stats; } ;
typedef  enum spu_utilization_state { ____Placeholder_spu_utilization_state } spu_utilization_state ;

/* Variables and functions */
 unsigned long long NSEC_PER_MSEC ; 
 scalar_t__ ktime_get_ns () ; 

__attribute__((used)) static unsigned long long spu_acct_time(struct spu *spu,
		enum spu_utilization_state state)
{
	unsigned long long time = spu->stats.times[state];

	/*
	 * If the spu is idle or the context is stopped, utilization
	 * statistics are not updated.  Apply the time delta from the
	 * last recorded state of the spu.
	 */
	if (spu->stats.util_state == state)
		time += ktime_get_ns() - spu->stats.tstamp;

	return time / NSEC_PER_MSEC;
}