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

/* Variables and functions */
 int ICC_PMR_EL1_PRIO_MASK ; 
 int /*<<< orphan*/  PMR ; 
 int /*<<< orphan*/  gic_icc_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
gic_v3_cpu_priority(uint64_t mask)
{

	/* Set prority mask */
	gic_icc_write(PMR, mask & ICC_PMR_EL1_PRIO_MASK);
}