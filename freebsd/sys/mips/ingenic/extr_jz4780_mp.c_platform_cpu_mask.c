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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ JZ4780_MAXCPU ; 

void
platform_cpu_mask(cpuset_t *mask)
{
	uint32_t i, m;

	CPU_ZERO(mask);
	for (i = 0, m = 1 ; i < JZ4780_MAXCPU; i++, m <<= 1)
		CPU_SET(i, mask);
}