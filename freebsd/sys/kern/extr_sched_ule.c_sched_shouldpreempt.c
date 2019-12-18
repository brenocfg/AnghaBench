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
 int PRI_MAX_INTERACT ; 
 int PRI_MIN_IDLE ; 
 int preempt_thresh ; 

__attribute__((used)) static inline int
sched_shouldpreempt(int pri, int cpri, int remote)
{
	/*
	 * If the new priority is not better than the current priority there is
	 * nothing to do.
	 */
	if (pri >= cpri)
		return (0);
	/*
	 * Always preempt idle.
	 */
	if (cpri >= PRI_MIN_IDLE)
		return (1);
	/*
	 * If preemption is disabled don't preempt others.
	 */
	if (preempt_thresh == 0)
		return (0);
	/*
	 * Preempt if we exceed the threshold.
	 */
	if (pri <= preempt_thresh)
		return (1);
	/*
	 * If we're interactive or better and there is non-interactive
	 * or worse running preempt only remote processors.
	 */
	if (remote && pri <= PRI_MAX_INTERACT && cpri > PRI_MAX_INTERACT)
		return (1);
	return (0);
}